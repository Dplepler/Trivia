package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.navigation.NavController
import com.example.trivia_android.BusinessLogic.Communications.Communications
import com.example.trivia_android.BusinessLogic.Communications.RequestCodes
import com.example.trivia_android.BusinessLogic.Communications.ResponseCodes
import com.example.trivia_android.BusinessLogic.Communications.Status
import kotlinx.coroutines.launch
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json


@Serializable
data class RoomInfo(val roomName: String, val maxUsers: Int, val questionCount: Int, val answerTimeout: Float)


class RoomsViewModel: ViewModel() {

    val comms = Communications

    val playerAmount = mutableStateOf("")

    val ansTime = mutableStateOf("")

    val roomName = mutableStateOf("")


    private val _playerList = mutableListOf<String>("Gal", "David")
    val playerList
        get() = _playerList



    fun createRoom(navController: NavController) {
        if(roomName.value.isEmpty() || playerAmount.value.isEmpty() || ansTime.value.isEmpty()) return
        viewModelScope.launch {
            val data = Json.encodeToString(
                RoomInfo(
                    roomName.value,
                    playerAmount.value.toInt(),
                    10,
                    ansTime.value.toFloat()
                )
            )
            comms.sendMessage(comms.buildMessage(RequestCodes.CreateRoom.code.toByte(), data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.CreateRoom.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) { navController.navigate("LobbyScreen") }
            }
        }
    }


}