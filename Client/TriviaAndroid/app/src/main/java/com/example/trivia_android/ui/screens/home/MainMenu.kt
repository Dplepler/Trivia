package com.example.trivia_android.ui.screens.home

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material.icons.filled.Home
import androidx.compose.material.icons.filled.Leaderboard
import androidx.compose.material.icons.filled.Logout
import androidx.compose.material.icons.outlined.AccountCircle
import androidx.compose.material.icons.outlined.Leaderboard
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.HomeViewModel
import com.example.trivia_android.BusinessLogic.ViewModels.RoomsViewModel
import com.example.trivia_android.ui.theme.TriviaAndroidTheme


@Composable
fun MainMenu(
    modifier: Modifier = Modifier,
    homeViewModel: HomeViewModel = viewModel(),
    roomsViewModel: RoomsViewModel = viewModel(),
    onClickCreate: () -> Unit = { }
) {

    val navController = rememberNavController()

    Scaffold(

        topBar = { MainMenuTopBar(homeViewModel.curScreen) },

        bottomBar = { MainMenuBotBar(homeViewModel.curScreen) },

    ) {
        NavHost(
            navController = navController,
            startDestination = "Home"
        ) {
            composable("Home") {
                HomeScreenContent(
                    onClickCreate = onClickCreate,
                    onClickJoin = { roomsViewModel.getRoomList() },
                    roomList = roomsViewModel.list.value
                )
            }
        }
    }
}


@Composable
fun MainMenuTopBar(
    text: String,
    onClickLogout: () -> Unit = { }
) {
    TopAppBar(
        backgroundColor = MaterialTheme.colors.surface
    ) {

        Text(
            text,
            modifier = Modifier.padding(start = 8.dp, end = 300.dp)
        )

        IconButton(onClick = { onClickLogout }) {
            Icon(Icons.Filled.Logout, "Logout button")
        }

    }
}




@Composable
fun MainMenuBotBar(
    curScreen: String
) {
    BottomAppBar(
        backgroundColor = MaterialTheme.colors.surface
    ) {
        HomeButton(curScreen = curScreen, modifier = Modifier.padding(end = 180.dp))

        IconButton(onClick = { /*TODO*/ }) {
            Icon(
                if(curScreen == "Stats") Icons.Filled.AccountCircle else Icons.Outlined.AccountCircle,
                "Personal stats button",
            )
        }

        Divider(
            modifier = Modifier
                .fillMaxHeight(0.8f)
                .width(1.dp)
        )


        IconButton(onClick = { /*TODO*/ }) {
            Icon(
                if(curScreen == "Podium") Icons.Filled.Leaderboard else Icons.Outlined.Leaderboard,
                "Global podium button",
            )
        }




    }
}



@Composable
fun HomeButton(
    curScreen: String,
    onClickButton: () -> Unit = { },
    modifier: Modifier = Modifier
) {
    Button(
        onClick = { onClickButton },
        colors = ButtonDefaults.buttonColors(
            backgroundColor = Color.Transparent
        ),
        modifier = if (curScreen == "Home") {
            modifier
                .border(width = 2.dp, MaterialTheme.colors.onBackground, MaterialTheme.shapes.small)
                .background(
                    brush = Brush.horizontalGradient(
                        colors = listOf(
                            MaterialTheme.colors.primary,
                            MaterialTheme.colors.secondary
                        )
                    ),
                    shape = MaterialTheme.shapes.small
                )
        } else {
            modifier
                .border(width = 2.dp, MaterialTheme.colors.onBackground, MaterialTheme.shapes.small)
        }
    ) {

        Icon(
            Icons.Filled.Home,
            "Home Icon",
            modifier = Modifier.padding(4.dp)
        )

        Text("Home")
    }
}



@Preview
@Composable
fun MainMenuPreview() {
    TriviaAndroidTheme() {
        Surface {
            MainMenuBotBar("Home")
        }
    }
}