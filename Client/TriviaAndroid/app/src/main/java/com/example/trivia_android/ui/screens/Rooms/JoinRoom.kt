package com.example.trivia_android.ui.screens.Rooms

import android.content.res.Configuration.UI_MODE_NIGHT_YES
import android.graphics.Paint
import androidx.compose.animation.AnimatedContent
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.ExperimentalAnimationApi
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@OptIn(ExperimentalAnimationApi::class)
@Composable
fun JoinRoomContent(
    modifier: Modifier = Modifier,
    roomNames: List<String>,
    onDismissRequest: () -> Unit = { },
    onClickRoom: (Int) -> Unit = { },
    popupWidth: Dp,
    popupHeight: Dp
) {



    AnimatedVisibility(true) {
        Box(
            modifier
                .size(popupWidth, popupHeight)
                .background(MaterialTheme.colors.background, MaterialTheme.shapes.large)
        ) {

            Column(modifier = Modifier.fillMaxWidth()) {

                Text(
                    "Pick a room:",
                    style = MaterialTheme.typography.overline,
                    color = MaterialTheme.colors.onBackground,
                    modifier = Modifier.padding(8.dp)
                )


                Divider(
                    modifier = Modifier
                        .fillMaxWidth()
                        .align(Alignment.CenterHorizontally),
                    thickness = 1.dp
                )


                LazyColumn(
                    modifier = Modifier
                        .fillMaxWidth()
                        .fillMaxHeight(0.9f),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) {

                    itemsIndexed(roomNames) { index: Int, name: String ->

                        Text(
                            name,
                            style = MaterialTheme.typography.body1.copy(
                                textAlign = TextAlign.Center
                            ),
                            color = MaterialTheme.colors.onBackground,
                            modifier = Modifier
                                .fillMaxWidth()
                                .padding(4.dp)
                                .clickable { onClickRoom(index) }
                        )


                        if (index != roomNames.lastIndex) {
                            Divider(
                                modifier = Modifier
                                    .fillMaxWidth(0.95f),
                                thickness = 1.dp
                            )
                        }

                    }

                }


                Divider(
                    modifier = Modifier
                        .fillMaxWidth()
                        .align(Alignment.CenterHorizontally),
                    thickness = 1.dp
                )


                IconButton(onClick = { onDismissRequest() }) {

                    Icon(
                        Icons.Filled.ArrowBack,
                        null,
                        tint = MaterialTheme.colors.onBackground
                    )

                }

            }

        }
    }
}






@Composable
@Preview
@Preview(
    name = "Popup dark preview",
    uiMode = UI_MODE_NIGHT_YES
)
fun PopupPreview() {
    TriviaAndroidTheme {

        val names = mutableListOf("room1", "room2", "room3")

        JoinRoomContent(
            roomNames = names,
            popupWidth = 299.dp,
            popupHeight = 479.dp
        )

    }
}