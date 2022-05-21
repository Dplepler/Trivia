package com.example.trivia_android.ui.screens.Rooms

import androidx.compose.runtime.Composable
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.RoomsViewModel
import com.example.trivia_android.ui.screens.authentication.MainAuthScreen
import com.example.trivia_android.ui.screens.home.MainMenu


@Composable
fun MainRoomScreen(roomsViewModel: RoomsViewModel = viewModel(), createOrJoin: Boolean) {

    val roomNavController = rememberNavController()

    NavHost(navController = roomNavController, startDestination = if(createOrJoin) "CreateRoom" else "JoinRoom") {


        composable("CreateRoom") {

            CreateRoom(
                roomName = roomsViewModel.roomName,
                playerVal = roomsViewModel.playerAmount,
                ansTimeVal = roomsViewModel.ansTime,
                onClickSubmit = { roomsViewModel.createRoom(roomNavController) },
                onSuccessCreate = {
                    roomNavController.navigate("LobbyScreen")
                },
            )
        }



        composable("LobbyScreen") {
            LobbyScreen(
                roomName = roomsViewModel.roomName.value,
                playerAmount = roomsViewModel.playerAmount.value,
                ansTime = roomsViewModel.ansTime.value,
                questionAmount = "10",
                playerList = roomsViewModel.playerList
            )
        }


    }

}