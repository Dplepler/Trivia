package com.example.trivia_android.BusinessLogic.Communications



import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import java.io.*
import java.net.Socket
import java.net.URISyntaxException


object Communications {

    const val addr = "10.0.2.2"
    const val port = 8008

    private lateinit var mSocket: Socket
    private lateinit var input: BufferedReader
    private lateinit var output: OutputStream


    suspend fun connectSocket() {
        withContext(Dispatchers.IO) {
            mSocket = Socket(addr, port)
            input = BufferedReader(InputStreamReader(mSocket.inputStream))
            output = mSocket.getOutputStream()
        }
    }


    suspend fun sendMessage(buffer: ByteArray) {
        withContext(Dispatchers.IO) {
            output.write(buffer)
        }
    }



    suspend fun readMessage(): ByteArray {
        var res: String? = null
        withContext(Dispatchers.IO) {
            kotlin.runCatching {
                res = input.readLine()
            }
        }
        return (if(res == null) byteArrayOf() else res?.toByteArray()!!)
    }


    fun buildMessage(code: Byte, data: String): ByteArray {
        val arr = byteArrayOf(code, 0, 0, 0, 0) + data.toByteArray()
        for (i in 0..3) arr[1 + i] = (data.length shr (24 - i*8)).toByte()
        return arr
    }




}