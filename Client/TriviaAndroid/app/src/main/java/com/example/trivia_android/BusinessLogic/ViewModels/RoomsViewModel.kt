package com.example.trivia_android.BusinessLogic.ViewModels


import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
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
data class RoomState(
    val status: Int,
    val name: String,
    val state: Int,
    val players: MutableList<String>,
    val questionCount: Int,
    val maxPlayers: Int,
    val answerTimeout: Float
)


enum class RoomStates(val state: Int) {
    Open(0),
    Closed(1),
    Started(2)
}




class RoomsViewModel: ViewModel() {

    val comms = Communications

    val playerAmount = mutableStateOf("")

    val ansTime = mutableStateOf("")

    val roomName = mutableStateOf("")

    private var id: Int = 0

    private var _roomList = mutableStateOf(RoomList())
    val roomList
        get() = _roomList



    private var _roomState = mutableStateOf(RoomState(0, "", RoomStates.Open.state, mutableListOf<String>(), 0, 0, 0f))
    val roomState
        get() = _roomState



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


    fun leaveRoom(onSuccessLeave: () -> Unit = { }) {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.LeaveRoom.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.LeaveRoom.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) { onSuccessLeave() }
            }
        }
    }



    fun closeRoom(onSuccessLeave: () -> Unit = { }) {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.CloseRoom.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.CloseRoom.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) { onSuccessLeave() }
            }
        }
    }



    fun startGame(onSuccessStart: () -> Unit = { }) {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.StartGame.code.toByte(), ""))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.StartGame.code) {
                val res = String(buffer).substring(comms.headerLen)
                if(Json.decodeFromString<Status>(res).status == 1) { onSuccessStart() }
            }
        }
    }





    fun getRoomState(onRoomClosed: () -> Unit = { }, onGameStart: () -> Unit = { }) {
        val data = Json.encodeToString(GetRoomDetails(id))
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.GetRoomState.code.toByte(), data))
            val buffer = comms.readMessage()
            if(buffer[0].toInt() == ResponseCodes.GetRoomState.code) {
                val res = String(buffer).substring(comms.headerLen)
                _roomState.value = Json.decodeFromString(res)
                if(_roomState.value.state == RoomStates.Closed.state) { onRoomClosed() }
                else if (_roomState.value.state == RoomStates.Started.state) { onGameStart() }
            }
        }
    }
}