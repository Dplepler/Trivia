package com.example.trivia_android.ui.screens.home




import android.content.res.Configuration.UI_MODE_NIGHT_YES
import androidx.compose.foundation.Image
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.ArrowForward
import androidx.compose.runtime.Composable
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
import androidx.constraintlayout.compose.ConstraintLayout
import com.example.trivia_android.ui.theme.TriviaAndroidTheme
import com.example.trivia_android.R


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





@Composable
fun HomeScreenContent(
    modifier: Modifier = Modifier,
    onClickCreate: () -> Unit = { },
    onClickJoin: () -> Unit = { }
) {


    ConstraintLayout(modifier = modifier.padding(8.dp)) {

        val (createRoom, joinRoom) = createRefs()

        RoomCard(
            Modifier.padding(16.dp)
                .constrainAs(createRoom) {
                top.linkTo(parent.top, margin = 4.dp)
                start.linkTo(parent.start, margin = 32.dp)
                end.linkTo(parent.end)
                bottom.linkTo(joinRoom.top, margin = 16.dp)
            },
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
                .constrainAs(joinRoom) {
                start.linkTo(parent.start, margin = 36.dp)
                end.linkTo(parent.end)
                bottom.linkTo(parent.bottom, margin = 4.dp)
            },
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
            onClickJoin
        )
        

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
            HomeScreenContent()
        }
    }
}

