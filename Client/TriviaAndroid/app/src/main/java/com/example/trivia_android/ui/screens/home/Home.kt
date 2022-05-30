package com.example.trivia_android.ui.screens.home




import android.content.res.Configuration.UI_MODE_NIGHT_YES
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.ExperimentalAnimationApi
import androidx.compose.foundation.Image
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.ArrowForward
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Alignment.Companion.CenterHorizontally
import androidx.compose.ui.Alignment.Companion.CenterVertically
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.window.Dialog
import androidx.compose.ui.window.Popup
import androidx.constraintlayout.compose.ConstraintLayout
import com.example.trivia_android.BusinessLogic.ViewModels.RoomList
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import com.example.trivia_android.R
import com.example.trivia_android.ui.screens.Rooms.JoinRoomContent


@Composable
fun RoomCard(
    modifier: Modifier = Modifier,
    roomText: String,
    buttonText: String,
    roomImage: Painter,
    buttonIcon: ImageVector,
    buttonColor: Color,
    onButtonClick: () -> Unit = { }
    ) {

    Card(
        modifier = modifier,
        elevation = 4.dp

    ) {


        Column() {


            Row(modifier = Modifier.padding(top = 24.dp, bottom = 8.dp)) {

                Image(
                    roomImage,
                    "Room Icon",
                    modifier = Modifier
                        .size(150.dp)
                        .align(CenterVertically)
                        .padding(start = 20.dp)
                )

                Text(
                    text = roomText,
                    modifier = Modifier
                        .align(CenterVertically)
                        .padding(start = 30.dp, end = 20.dp),
                    style = MaterialTheme.typography.h4
                )

            }


            Button(
                onClick = { onButtonClick() },
                modifier = Modifier.padding(8.dp),
                colors = ButtonDefaults.buttonColors (backgroundColor = buttonColor)
            ) {

                Text(buttonText, modifier = Modifier.padding(end = 36.dp))

                Icon(buttonIcon, "Button Icon")

            }

        }

    }

}





@OptIn(ExperimentalAnimationApi::class)
@Composable
fun HomeScreenContent(
    modifier: Modifier = Modifier,
    onClickCreate: () -> Unit = { },
    onJoinRefresh: () -> Unit = { },
    onClickRoom: (Int) -> Unit = { },
    roomList: RoomList
) {

    var expanded by remember { mutableStateOf(false) }


    Column(
        modifier = modifier
            .fillMaxWidth()
            .fillMaxHeight(0.9f)
            .padding(8.dp),
        verticalArrangement = Arrangement.SpaceEvenly
    ) {

        RoomCard(
            Modifier
                .align(CenterHorizontally),
            "Create\nRoom",
            "Create a new game room!",
            painterResource(
                id =
                if (isSystemInDarkTheme()) {
                    R.drawable.ic_createroomicondark
                } else {
                    R.drawable.ic_createroomicon
                }
            ),
            Icons.Filled.Add,
            MaterialTheme.colors.primary,
            onClickCreate
        )


        RoomCard(
            Modifier
                .align(CenterHorizontally),
            "Join\nRoom",
            "Join an existing game room!",
            painterResource(
                id =
                if (isSystemInDarkTheme()) {
                    R.drawable.ic_joinroomicondark
                } else {
                    R.drawable.ic_joinroomicon
                }
            ),
            Icons.Filled.ArrowForward,
            MaterialTheme.colors.secondary,
            onButtonClick = { expanded = true }
        )
    }


    AnimatedVisibility(expanded) {
        Dialog(onDismissRequest = { expanded = false }) {
            JoinRoomContent(
                onRefresh = onJoinRefresh,
                roomList = roomList,
                onDismissRequest = { expanded = false },
                onClickRoom = onClickRoom,
                popupWidth = 299.dp,
                popupHeight = 479.dp
            )
        }
    }

}







@Preview
@Preview(
    name = "Dark Mode Preview",
    uiMode = UI_MODE_NIGHT_YES
)
@Composable
fun RoomCardPreview() {

    TriviaAndroidTheme {

        RoomCard(
            Modifier,
            "Join\nRoom",
            "Join an existing game room!",
            painterResource(
                id =
                if (isSystemInDarkTheme()) {
                    R.drawable.ic_joinroomicondark
                } else {
                    R.drawable.ic_joinroomicon
                }
            ),
            Icons.Filled.ArrowForward,
            MaterialTheme.colors.secondary
        )

    }
}




@Preview
@Preview(
    name = "Home Dark Preview",
    uiMode = UI_MODE_NIGHT_YES
)
@Composable
fun HomeScreenPreview() {
    TriviaAndroidTheme {


        Surface {
            HomeScreenContent(roomList = RoomList())
        }
    }
}


