package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.trivia_android.BusinessLogic.Communications.*
import kotlinx.coroutines.launch
import kotlinx.serialization.*
import kotlinx.serialization.encoding.Decoder
import kotlinx.serialization.json.*


@Serializable
data class Question(
    val status: Int,
    val question: String,
    val answers: List<String>
)


@Serializable
data class CorrectAnswer (
    val status: Int,
    val correctAns: Int
)


@Serializable
data class AnswerSubmition(val answerId: Int)



data class UserResults(
    val username: String,
    val averageTime: Int,
    val correctAns: Int,
    val wrongAns: Int
)



@Serializable
data class GameResults (
    val status: Int,
    val names: List<String>,
    val correct: List<Int>,
    val wrong: List<Int>,
    val time: List<Int>
)









data class UserScore(val username: String, val score: Int)



class GameViewModel: ViewModel() {

    val comms = Communications

    val userInfo = UserInfo

    val gameInfo = GameInfo

    val curQuestion = mutableStateOf( Question(0, "", listOf(" ", " ", " ", " ")))

    val correctAnswerId = mutableStateOf( -1 )

    val chosenAnswer = mutableStateOf( 1 )

    val questionNumber = mutableStateOf( 0 )

    val curTime = mutableStateOf( 0 )

    val userScores = mutableStateListOf<UserScore>()

    val userStats = mutableStateOf(UserResults(" ", 0, 0, 0))

    companion object {
        const val SCORE_MULTIPLIER = 10000
    }


    fun getQuestion() {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.GetQuestion.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.GetQuestion.code) {
                val res = String(buffer).substring(comms.headerLen)
                curQuestion.value = Json.decodeFromString(res)
                chosenAnswer.value = -1
                correctAnswerId.value = -1
                questionNumber.value++
                curTime.value = gameInfo.answerTimeout.toInt()
            }
        }
    }


    fun submitQuestion(answerId: Int) {
        viewModelScope.launch {
            val data = Json.encodeToString(AnswerSubmition(answerId))
            comms.sendMessage(comms.buildMessage(RequestCodes.SubmitAnswer.code.toByte(), data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.SubmitAns.code) {
                val res = String(buffer).substring(comms.headerLen)
                correctAnswerId.value = Json.decodeFromString<CorrectAnswer>(res).correctAns
                chosenAnswer.value = answerId
            }
        }
    }




    fun getResults() {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.GameResult.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.GetResults.code) {
                var res = String(buffer).substring(comms.headerLen)
                val resObj = Json.decodeFromString<GameResults>(res)
                val resList = mutableListOf<UserResults>()
                for(i in 0..resObj.names.lastIndex) {
                    resList.add(
                        UserResults(
                            resObj.names[i],
                            resObj.time[i],
                            resObj.correct[i],
                            resObj.wrong[i]
                    ))
                }
                createScores(resList)
            }
        }
    }



    private fun createScores(userResults: List<UserResults>) {

        userScores.clear()

        userResults.forEach {
            if(it.username == userInfo.userName) { userStats.value = it }

            userScores.add(UserScore(it.username, calcScore(it).toInt()))
        }

        userScores.sortBy { it.score }
    }


    private fun calcScore(userResults: UserResults): Float =
        if(userResults.averageTime == 0) 0f
        else userResults.correctAns / (userResults.correctAns + userResults.wrongAns) * SCORE_MULTIPLIER / userResults.averageTime.toFloat()



    fun leaveGame(onSuccessLeave: () -> Unit = { }) {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.LeaveGame.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.LeaveGame.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) { onSuccessLeave }
            }
        }
    }


    fun decreaseTime(onGameEnd: () -> Unit = { }) {
        curTime.value = (curTime.value - 1)
        if(curTime.value <= 0) {
            if(questionNumber.value >= gameInfo.questionCount) {
                onGameEnd()
                curTime.value = 0
            }
            else {
                if (chosenAnswer.value == -1) {
                    submitQuestion(-1)
                }
                getQuestion()
            }
        }

    }


}