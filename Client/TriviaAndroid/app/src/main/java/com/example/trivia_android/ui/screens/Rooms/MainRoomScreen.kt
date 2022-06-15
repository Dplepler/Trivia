package com.example.trivia_android.ui.screens.Rooms

import android.widget.Toast
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.RoomsViewModel
import com.example.trivia_android.ui.screens.authentication.MainAuthScreen
import com.example.trivia_android.ui.screens.home.MainMenu


@Composable
fun MainRoomScreen(
    roomsViewModel: RoomsViewModel = viewModel(),
    createOrJoin: Boolean,
    leaveToMenu: () -> Unit = { },
    getInGame: () -> Unit = { }
) {

    val roomNavController = rememberNavController()
    val curContext = LocalContext.current

    NavHost(navController = roomNavController, startDestination = if(createOrJoin) "CreateRoom" else "LobbyScreen") {


        composable("CreateRoom") {

            CreateRoom(
                roomName = roomsViewModel.roomName,
                playerVal = roomsViewModel.playerAmount,
                ansTimeVal = roomsViewModel.ansTime,
                onClickSubmit = { roomsViewModel.createRoom() { roomNavController.navigate("LobbyScreen") } },
            )
        }



        composable("LobbyScreen") {
            LobbyScreen(
                roomState = roomsViewModel.roomState.value,
                onRefresh = {
                    roomsViewModel.getRoomState(
                        onRoomClosed = {
                            Toast.makeText(curContext, "Room closed by admin!", Toast.LENGTH_LONG).show()
                            roomsViewModel.leaveRoom(leaveToMenu)
                        },
                        onGameStart = getInGame
                    )
                },
                onClickLeave = if(createOrJoin) { {roomsViewModel.closeRoom(leaveToMenu)} } else { { roomsViewModel.leaveRoom(leaveToMenu) } },
                onClickStart = if(createOrJoin) { {roomsViewModel.startGame(onSuccessStart = getInGame)} } else { { } },
            )
        }
    }
}