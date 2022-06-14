package com.example.trivia_android.ui.screens.game

import android.widget.Toast
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.trivia_android.BusinessLogic.ViewModels.GameViewModel
import com.example.trivia_android.ui.screens.game.gameScreen.GameScreen


@Composable
fun MainGameScreen(
    gameViewModel: GameViewModel = viewModel()
) {
    val gameNavController = rememberNavController()
    val localContext = LocalContext.current

    NavHost(navController = gameNavController, startDestination = "Game") {

        composable("Game") {
            GameScreen(
                curQuestion = gameViewModel.curQuestion.value,
                questionNumber = gameViewModel.questionNumber.value,
                totalQuestions = gameViewModel.gameInfo.questionCount,
                curTime = gameViewModel.curTime.value,
                correctAnswer = gameViewModel.correctAnswerId.value,
                chosenAnswer = gameViewModel.chosenAnswer.value,
                submitted = (gameViewModel.chosenAnswer.value != -1),
                decreaseTime = { gameViewModel.decreaseTime() { Toast.makeText(localContext, "Game Over!", Toast.LENGTH_LONG).show() } },
                submitAnswer = { gameViewModel.submitQuestion(it) }
            )
        }

    }
}