package com.example.trivia_android.BusinessLogic.ViewModels

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.trivia_android.BusinessLogic.Communications.Communications
import com.example.trivia_android.BusinessLogic.Communications.RequestCodes
import com.example.trivia_android.BusinessLogic.Communications.ResponseCodes
import kotlinx.coroutines.launch
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json

@Serializable
data class Stats(
    val status: Int = 0,
    val statistics: List<String> = listOf("0", "0", "0", "0")
)

enum class StatIndex(val index: Int) {

    gamesPlayed(0),
    correctAns(1),
    totalAns(2),
    avgTime(3)
}

class HomeViewModel: ViewModel() {

    var curScreen by mutableStateOf("Home")
    val comms = Communications

    private var _stats = mutableStateOf(Stats())
    val stats
        get() = _stats

    fun getStats() {
        viewModelScope.launch {
            comms.sendMessage(comms.buildMessage(RequestCodes.Stats.code.toByte(), ""))
            val buffer = comms.readMessage()
            // checks that the response is relevant and not an error
            if(buffer[0].toInt() == ResponseCodes.Stats.code) {
                val res = String(buffer).substring(comms.headerLen)
                stats.value = Json.decodeFromString(res)
            }
        }
    }
}