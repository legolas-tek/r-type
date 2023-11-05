/*
** EPITECH PROJECT, 2023
** R-Type Game
** File description:
** Score Manager
*/

#include "ScoreManager.hpp"
#include "Entity.hpp"

#include <fstream>

ScoreManager::ScoreManager(Component::Text &scoreText)
    : _scoreText(scoreText)
    , _score(0)
{
    _score = 0;
    std::ifstream highscoreFile(HIGHSCORE_FILE);
    if (highscoreFile.is_open()) {
        highscoreFile >> _highscore;
    } else {
        _highscore = 0;
    }
    addScore(0); // Update score text
}

ScoreManager::~ScoreManager()
{
    std::ofstream highscoreFile(
        HIGHSCORE_FILE, std::ofstream::out | std::ofstream::trunc
    );
    if (highscoreFile.is_open()) {
        highscoreFile << _highscore;
    }
}

void ScoreManager::addScore(int score)
{
    _score += score;
    if (_score > _highscore)
        _highscore = _score;
    _scoreText._text = "Score " + std::to_string(_score) + "\nHighscore "
        + std::to_string(_highscore);
}
