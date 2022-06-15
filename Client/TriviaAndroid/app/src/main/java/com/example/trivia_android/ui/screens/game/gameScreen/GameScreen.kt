package com.example.trivia_android.ui.screens.game.gameScreen

import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Alarm
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import com.example.trivia_android.BusinessLogic.ViewModels.CorrectAnswer
import com.example.trivia_android.BusinessLogic.ViewModels.Question
import com.example.trivia_android.ui.screens.game.AnswerButton
import com.example.trivia_android.ui.screens.game.CorrectButton
import com.example.trivia_android.ui.screens.game.IncorrectButton
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import kotlinx.coroutines.delay


@Composable
fun GameScreen(
    curQuestion: Question,
    questionNumber: Int,
    totalQuestions: Int,
    curTime: Int = 90,
    correctAnswer: Int = -1,
    chosenAnswer: Int = -1,
    submitted: Boolean = false,
    decreaseTime: () -> Unit = { },
    submitAnswer: (Int) -> Unit = { }
) {

    Scaffold(

        topBar = {
            TopAppBar(backgroundColor = MaterialTheme.colors.background) {
                Text(
                    "Q $questionNumber/$totalQuestions",
                    color = MaterialTheme.colors.onBackground.copy(0.4f),
                    modifier = Modifier
                        .padding(start = 4.dp)
                        .align(Alignment.CenterVertically)
                )
            }
        },


        bottomBar = {
            BottomAppBar(backgroundColor = MaterialTheme.colors.background) {
                Row(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalArrangement = Arrangement.Center,
                    verticalAlignment = Alignment.CenterVertically
                ) {
                    GameTimer(curTime)
                }
            }
        }

    ) {

        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(bottom = 60.dp),
            verticalArrangement = Arrangement.SpaceEvenly,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {

            Text(
                curQuestion.question,
                style = MaterialTheme.typography.h5.copy(textAlign = TextAlign.Center)
            )

            for(i in 0..3) {
                if(correctAnswer == i) {
                    CorrectButton(answerText = curQuestion.answers[i])
                }
                else if (chosenAnswer == i) {
                    IncorrectButton(answerText = curQuestion.answers[i])
                }
                else {
                    AnswerButton(
                        answerText = curQuestion.answers[i],
                        enabled = !submitted,
                        onClick = { submitAnswer(i) }
                    )
                }
            }
        }
    }

    LaunchedEffect(Unit) {
        while(true) {
            decreaseTime()
            delay(1000)
        }
    }
}


@Composable
fun GameTimer(
    timeInSeconds: Int = 90,
    height: Dp = 40.dp,
    width: Dp = 102.dp
) {
    Box(
        Modifier
            .height(height)
            .width(width)) {
        Surface(color = MaterialTheme.colors.secondary) {
            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(4.dp),
                horizontalArrangement = Arrangement.Center,
                verticalAlignment = Alignment.CenterVertically
            ) {

                Icon(
                    Icons.Filled.Alarm,
                    null,
                    modifier = Modifier.padding(end = 8.dp)
                )

                Text("" +
                        "${ 
                            if (timeInSeconds / 60 < 10) "0${timeInSeconds / 60}"
                            else timeInSeconds / 60
                        }" + ":" +
                        "${
                            if (timeInSeconds % 60 < 10) "0${timeInSeconds % 60}"
                            else timeInSeconds % 60
                        }"
                )

            }
        }
    }
}



@Composable
@Preview
fun TimerPreview() {
    TriviaAndroidTheme {

        GameTimer(timeInSeconds = 180)

    }
}



@Composable
@Preview
fun gameScreenPreview() {
    TriviaAndroidTheme {
        GameScreen(
            curQuestion = Question(0, "sugoma", listOf(" ", " ", " ", " ")),
            questionNumber = 2,
            totalQuestions = 6,
            chosenAnswer = 2,
            correctAnswer = 2
        )
    }
}