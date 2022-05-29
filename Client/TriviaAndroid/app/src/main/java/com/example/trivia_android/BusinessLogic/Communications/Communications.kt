package com.example.trivia_android.BusinessLogic.Communications



import android.util.Log
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import kotlinx.serialization.Serializable
import java.io.*
import java.net.Socket
import java.net.SocketAddress
import java.net.URISyntaxException



@Serializable
data class Status(val status: Int)


enum class RequestCodes(val code: Int) {
    Signup(11),
    Login(12),
    CreateRoom(13),
    GetRooms(14),
    GetRoomState(15),
    JoinRoom(16),
    Stats(17),
    HighScore(18),
    Logout(19),
    StartGameCode(31),
    CloseRoomCode(32),
    LeaveRoomCode(33)
}


enum class ResponseCodes(val code: Int) {
    Signup(21),
    Login(22),
    Logout(23),
    GetRooms(24),
    GetRoomPlayers(25),
    HighScore(26),
    Stats(27),
    JoinRoom(28),
    CreateRoom(29),
    Error(40)
}




object Communications {

    private const val addr = "10.0.2.2"
    private const val port = 8008
    private const val shiftStart = 24
    private const val shiftOffset = 8
    const val headerLen = 5

    private lateinit var mSocket: Socket
    private lateinit var input: BufferedReader
    private lateinit var output: OutputStream


    suspend fun connectSocket() {
        withContext(Dispatchers.IO) {
            try {
                mSocket = Socket(addr, port)
                input = BufferedReader(InputStreamReader(mSocket.inputStream))
                output = mSocket.getOutputStream()
            } catch (ex: Throwable) { /* skipped */ }
        }
    }



    suspend fun closeSocket() {
        withContext(Dispatchers.IO) {
            try {
                mSocket.close()
            } catch(ex: Throwable) { /* skipped */ }
        }
    }




    suspend fun sendMessage(buffer: ByteArray) {
        try {
            withContext(Dispatchers.IO) {
                output.write(buffer)
            }
        } catch (ex: Throwable) {
            kotlin.runCatching {
                // error case, tries to close the socket and reconnect
                mSocket.close()
                connectSocket()
            }
        }
    }



    suspend fun readMessage(): ByteArray {
        var res: String? = null
        try {
            withContext(Dispatchers.IO) {
                res = input.readLine()
                Log.i("success", res!!)
            }
        } catch(ex: Throwable) {
            kotlin.runCatching {
                // error case, tries to close the socket and reconnect
                mSocket.close()
                connectSocket()
            }
        }
        return (if(res == null) byteArrayOf(0) else res?.toByteArray()!!)
    }


    // Builds a message in the protocol format
    fun buildMessage(code: Byte, data: String): ByteArray {
        val arr = byteArrayOf(code, 0, 0, 0, 0) + data.toByteArray()
        for (i in 0..3) arr[1 + i] = (data.length shr (shiftStart - i* shiftOffset)).toByte()
        return arr
    }

}