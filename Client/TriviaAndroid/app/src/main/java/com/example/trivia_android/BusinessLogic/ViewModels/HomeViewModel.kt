package com.example.trivia_android.BusinessLogic.ViewModels

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.trivia_android.BusinessLogic.Communications.Communications
import com.example.trivia_android.BusinessLogic.Communications.RequestCodes
import com.example.trivia_android.BusinessLogic.Communications.ResponseCodes
import kotlinx.coroutines.launch
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json


class HomeViewModel: ViewModel() {

    var curScreen by mutableStateOf("Home")
    val comms = Communications

    private var _totalAnswers by mutableStateOf(0.0f)
    val totalAnswers
        get() = _totalAnswers

    private var _correctAnswers by mutableStateOf(0.0f)
    val correctAnswers
        get() = _correctAnswers

    private var _avgTime by mutableStateOf(0.0f)
    val avgTime
        get() = _avgTime

    private var _gamesPlayed by mutableStateOf(0.0f)
    val gamesPlayed
        get() = _gamesPlayed

    fun getStats() {

        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.Login.code.toByte(), ""))
            val buffer = comms.readMessage()
            // checks that the response is relevant and not an error
            if(buffer[0].toInt() == ResponseCodes.Stats.code) {
                val res = String(buffer).substring(comms.headerLen)
            }
        }

    }

}