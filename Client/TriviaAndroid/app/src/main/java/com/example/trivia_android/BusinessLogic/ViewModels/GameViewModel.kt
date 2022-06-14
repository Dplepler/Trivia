package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.trivia_android.BusinessLogic.Communications.Communications
import com.example.trivia_android.BusinessLogic.Communications.RequestCodes
import com.example.trivia_android.BusinessLogic.Communications.ResponseCodes
import kotlinx.coroutines.launch
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json


@Serializable
data class Question(
    val status: Int,
    val question: String,
    val answers: Map<Int, String>
)


@Serializable
data class CorrectAnswer (
    val status: Int,
    val correctAns: Int
)


@Serializable
data class AnswerSubmition(val answerId: Int)


class GameViewModel: ViewModel() {

    val comms = Communications

    val gameInfo = GameInfo

    val curQuestion = mutableStateOf( Question(0, "", mapOf<Int, String>(1 to " ", 2 to " ", 3 to " ", 4 to " ")))

    val correctAnswerId = mutableStateOf( -1 )

    val chosenAnswer = mutableStateOf( -1 )

    val questionNumber = mutableStateOf( 0 )

    val curTime = mutableStateOf( 0 )

    
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
                curTime.value = 60
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
            }
        }
    }


}