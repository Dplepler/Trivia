package com.example.trivia_android.ui.screens.game.resultScreen

import androidx.compose.foundation.layout.*
import androidx.compose.material.Card
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun ScoreCard(
    modifier: Modifier = Modifier,
    score: Int = 0,
    name: String = " "
) {

    Card(
        backgroundColor = MaterialTheme.colors.secondary,
        contentColor = MaterialTheme.colors.onSecondary,
        modifier = modifier
            .width(305.dp)
            .height(95.dp)
    ) {
        Column (
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {

            Text(name, style = MaterialTheme.typography.h4)

            Text(
                score.toString(),
                color = MaterialTheme.colors.onSecondary.copy(0.6f),
                style = MaterialTheme.typography.h4,
                modifier = Modifier.padding(bottom = 4.dp)
            )
        }
    }
}


@Composable
@Preview
fun ScoreCardPreview() {
    TriviaAndroidTheme {

        ScoreCard(score = 923, name = "David")

    }
}



