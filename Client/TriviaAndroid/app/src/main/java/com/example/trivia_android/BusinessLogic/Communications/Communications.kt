package com.example.trivia_android.BusinessLogic.Communications



import android.util.Log
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import java.io.*
import java.net.Socket
import java.net.SocketAddress
import java.net.URISyntaxException


object Communications {

    private const val addr = "10.0.2.2"
    private const val port = 8008

    private lateinit var mSocket: Socket
    private lateinit var input: BufferedReader
    private lateinit var output: OutputStream


    suspend fun connectSocket() {
        withContext(Dispatchers.IO) {
            try {
                mSocket = Socket(addr, port)
                input = BufferedReader(InputStreamReader(mSocket.inputStream))
                output = mSocket.getOutputStream()
            } catch (ex: Throwable) {

            }
        }
    }


    suspend fun sendMessage(buffer: ByteArray) {
        try {
            withContext(Dispatchers.IO) {
                output.write(buffer)
            }
        } catch (ex: Throwable) {
            kotlin.runCatching {
                mSocket.close()
                connectSocket()
            }
        }
    }



    suspend fun readMessage(): ByteArray {
        var res: String? = null
        try {
            withContext(Dispatchers.IO) {
                kotlin.runCatching {
                    res = input.readLine()
                }
            }
        } catch(ex: Throwable) {
            kotlin.runCatching {
                mSocket.close()
                connectSocket()
            }
        }
        return (if(res == null) byteArrayOf(0) else res?.toByteArray()!!)
    }


    fun buildMessage(code: Byte, data: String): ByteArray {
        val arr = byteArrayOf(code, 0, 0, 0, 0) + data.toByteArray()
        for (i in 0..3) arr[1 + i] = (data.length shr (24 - i*8)).toByte()
        return arr
    }




}