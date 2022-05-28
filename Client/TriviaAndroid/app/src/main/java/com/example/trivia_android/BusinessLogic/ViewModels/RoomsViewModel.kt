package com.example.trivia_android.BusinessLogic.ViewModels

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.navigation.NavController
import com.example.trivia_android.BusinessLogic.Communications.*
import kotlinx.coroutines.launch
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json



@Serializable
data class RoomInfo(val roomName: String, val maxUsers: Int, val questionCount: Int, val answerTimeout: Float)

@Serializable
data class RoomList(val status: Int = 0, val names: List<String> = listOf(), val ids: List<Int> = listOf())

@Serializable
data class GetRoomDetails(val roomId: Int)

@Serializable
data class PlayerList(val players: MutableList<String>)


class RoomsViewModel: ViewModel() {

    val comms = Communications

    val userInfo = UserInfo

    val playerAmount = mutableStateOf("")

    val ansTime = mutableStateOf("")

    val roomName = mutableStateOf("")

    private var id: Int = 0

    private var _roomList = mutableStateOf(RoomList())
    val roomList
        get() = _roomList



    private var _playerList = mutableStateListOf<String>()
    val playerList
        get() = _playerList



    fun createRoom(onSuccess: () -> Unit) {
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
                if(Json.decodeFromString<Status>(res).status == 1) { onSuccess() }
            }
        }
    }



    fun joinRoom(roomId: Int, onSuccess: () -> Unit) {
        val data = Json.encodeToString(GetRoomDetails(roomId))
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.JoinRoom.code.toByte(), data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.JoinRoom.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) {
                    id = roomId
                    onSuccess()
                }
            }
        }
    }




    fun getRoomList() {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.GetRooms.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.GetRooms.code) {
                val res = String(buffer).substring(comms.headerLen)
                _roomList.value = Json.decodeFromString(res)
            }
        }
    }


    fun getUserList() {
        val data = Json.encodeToString(GetRoomDetails(id))
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.GetRoomPlayers.code.toByte(), data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.GetRoomPlayers.code) {
                val res = String(buffer).substring(comms.headerLen)
                val list = Json.decodeFromString<PlayerList>(res)
                _playerList.clear()
                _playerList.addAll(list.players)
            }
        }
    }
}