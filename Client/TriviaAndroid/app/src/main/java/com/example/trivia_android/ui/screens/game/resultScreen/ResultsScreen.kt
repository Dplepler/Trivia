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
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun ResultsScreen(
    userList: List<String>
) {

    Scaffold (
        topBar = {
            TopAppBar(backgroundColor = MaterialTheme.colors.background) {
                IconButton(
                    onClick = { /*TODO*/ },
                    modifier = Modifier.padding(end = 4.dp)
                ) { Icon(Icons.Filled.ArrowBack, null) }

                Text("MyRoom")
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

                StatBox(statValue = 6f)

                StatBox(statIcon = Icons.Filled.Cancel, statValue = 9f)

                StatBox(statIcon = Icons.Filled.Alarm, statValue = 6.5f)

            }


            Divider(
                modifier = Modifier.fillMaxWidth().padding(top = 16.dp),
                thickness = 1.dp,
                color = MaterialTheme.colors.onSurface.copy(0.7f)
            )



            LazyColumn(
                modifier = Modifier.fillMaxSize(),
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.SpaceBetween
            ) {

                items(userList) {

                    ScoreCard(score = 69, name = it, modifier = Modifier.padding(16.dp))

                }
            }
        }
    }
}



@Composable
@Preview
fun ResultsScreenPreview() {
    TriviaAndroidTheme {

        ResultsScreen(userList = listOf("Gal", "David", "Sugoma", "Hello", "Bye", "Sus", "Gay", "Cringe"))

    }
}




