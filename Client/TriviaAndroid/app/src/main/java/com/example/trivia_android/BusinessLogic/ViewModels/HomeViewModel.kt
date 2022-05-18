package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import com.example.trivia_android.BusinessLogic.Communications.Communications
import kotlinx.serialization.Serializable


@Serializable
data class RoomInfo(val roomName: String, val maxUsers: Int, val questionCount: Int, val answerTimeout: Float)


class HomeViewModel: ViewModel() {

    var curScreen by mutableStateOf("Home")
    val comms = Communications

}