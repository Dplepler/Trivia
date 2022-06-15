package com.example.trivia_android.ui.screens.game.resultScreen

import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Alarm
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.Cancel
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.BusinessLogic.ViewModels.UserResults
import com.example.trivia_android.BusinessLogic.ViewModels.UserScore
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import kotlinx.coroutines.delay


@Composable
fun ResultsScreen(
    userRes: UserResults = UserResults("", 0, 0, 0),
    userList: List<UserScore>,
    roomName: String = " ",
    userName: String = " ",
    getGameRes: () -> Unit = { },
    onClickLeave: () -> Unit = { }
) {

    Scaffold (
        topBar = {
            TopAppBar(backgroundColor = MaterialTheme.colors.background) {
                IconButton(
                    onClick = onClickLeave,
                    modifier = Modifier.padding(end = 4.dp)
                ) { Icon(Icons.Filled.ArrowBack, null) }

                Text(roomName)
            }
        }
    ) {

        Column(
            modifier = Modifier.fillMaxSize(),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {

            Text(
                "Results",
                style = MaterialTheme.typography.h6,
                modifier = Modifier.padding(8.dp)
            )


            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(4.dp),
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.SpaceEvenly
            ) {

                StatBox(statValue = userRes.correctAns.toFloat())

                StatBox(statIcon = Icons.Filled.Cancel, statValue = userRes.wrongAns.toFloat())

                StatBox(statIcon = Icons.Filled.Alarm, statValue = userRes.averageTime.toFloat())

            }


            Divider(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp),
                thickness = 1.dp,
                color = MaterialTheme.colors.onSurface.copy(0.7f)
            )



            LazyColumn(
                modifier = Modifier.fillMaxSize(),
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.SpaceBetween
            ) {

                items(userList) {
                    ScoreCard(
                        score = it.score,
                        name = if(it.username == userName) "${it.username} (You)" else it.username,
                        modifier = Modifier.padding(16.dp)
                    )
                }
            }
        }
    }

    LaunchedEffect(Unit) {
        while(true) {
            getGameRes()
            delay(3000)
        }
    }

}



@Composable
@Preview
fun ResultsScreenPreview() {
    TriviaAndroidTheme {

        ResultsScreen(userList = listOf<UserScore>())

    }
}




