package com.example.trivia_android.ui.screens.home

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.layout.*
import androidx.compose.material.Card
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.CheckCircle
import androidx.compose.material.icons.filled.ModeEdit
import androidx.compose.material.icons.filled.QuestionAnswer
import androidx.compose.material.icons.filled.Timer
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.BusinessLogic.ViewModels.Leaderboard
import com.example.trivia_android.BusinessLogic.ViewModels.StatIndex
import com.example.trivia_android.BusinessLogic.ViewModels.Stats
import com.example.trivia_android.ui.theme.*
import java.text.DecimalFormat
import java.text.DecimalFormatSymbols
import java.util.*

@Composable
fun LeaderboardCard(
    modifier: Modifier = Modifier,
    value: Float,
    backgroundColor: Color = Marine700,
    name: String
) {

    val otherSymbols = DecimalFormatSymbols(Locale.US)
    val df = DecimalFormat("#.##########", otherSymbols)

    Card(modifier = modifier, elevation = 8.dp, backgroundColor = backgroundColor, border = BorderStroke(1.dp, Color.Black)) {

        Row() {

            Column(modifier = Modifier.align(Alignment.CenterVertically).fillMaxWidth().padding(end = 8.dp)) {

                Text(
                    text = name,
                    color = Color.White,
                    modifier = Modifier

                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.h5
                )
                Text(
                    text = df.format(value),
                    color = Color.White.copy(0.8f),
                    modifier = Modifier
                        .align(Alignment.CenterHorizontally),
                    style = MaterialTheme.typography.h4
                )
            }
        }
    }
}

@Composable
fun LeaderboardScreenContent(
    leaderboard: Leaderboard = Leaderboard()
) {
    Column() {

        Text(
            text = "Leaderboard",
            modifier = Modifier
                .align(Alignment.CenterHorizontally),
            style = MaterialTheme.typography.h4.copy(fontWeight = FontWeight.Bold)

        )

        LeaderboardCard(
            value = 1f,
            backgroundColor = Marine700,
            name = leaderboard.HighScores[0],
            modifier = Modifier.padding(16.dp)
        )

        LeaderboardCard(
            value = 2f,
            backgroundColor = Marine500,
            name = leaderboard.HighScores[1],
            modifier = Modifier.padding(16.dp)
        )

        LeaderboardCard(
            value = 3f,
            backgroundColor = Marine400,
            name = leaderboard.HighScores[2],
            modifier = Modifier.padding(16.dp)
        )

        LeaderboardCard(
            value = 4f,
            backgroundColor = Blue600,
            name = leaderboard.HighScores[3],
            modifier = Modifier.padding(16.dp)
        )

        LeaderboardCard(
            value = 5f,
            backgroundColor = Marine200,
            name = leaderboard.HighScores[4],
            modifier = Modifier.padding(16.dp)
        )
    }
}

@Composable
@Preview
fun LeaderboardScreenInit() {


    TriviaAndroidTheme() {
        Column() {
            LeaderboardCard(value = 300000f, name = "Ron Buzaglo",
                modifier = Modifier.padding(8.dp))
            LeaderboardCard(value = 200000f, name = "Ben Shapiro",
                modifier = Modifier.padding(8.dp))
            LeaderboardCard(value = 100000f, name = "Muhammad Ali",
                modifier = Modifier.padding(8.dp))
            LeaderboardCard(value = 10000f, name = "Shimi Tavori",
                modifier = Modifier.padding(8.dp))
            LeaderboardCard(value = 1000f, name = "Static & BenEL",
                modifier = Modifier.padding(8.dp))
        }

    }
}