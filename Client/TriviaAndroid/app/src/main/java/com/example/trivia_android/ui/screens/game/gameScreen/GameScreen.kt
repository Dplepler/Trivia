package com.example.trivia_android.ui.screens.game.gameScreen

import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Alarm
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.screens.game.AnswerButton
import com.example.trivia_android.ui.theme.TriviaAndroidTheme




@Composable
fun GameScreen(
    curQuestion: Int,
    totalQuestions: Int,
    questionText: String
) {

    Scaffold(

        topBar = {
            TopAppBar(backgroundColor = MaterialTheme.colors.background) {
                Text(
                    "Q $curQuestion/$totalQuestions",
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
                    GameTimer()
                }
            }
        }

    ) {

        Column(
            modifier = Modifier.fillMaxSize().padding(bottom = 60.dp),
            verticalArrangement = Arrangement.SpaceEvenly,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {

            Text(questionText, style = MaterialTheme.typography.h5)

            AnswerButton()

            AnswerButton()

            AnswerButton()

            AnswerButton()
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
            curQuestion = 2,
            totalQuestions = 6,
            questionText = "sugoma"
        )
    }
}