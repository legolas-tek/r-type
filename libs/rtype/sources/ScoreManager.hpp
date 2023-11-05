/*
** EPITECH PROJECT, 2023
** R-Type Game
** File description:
** Score Manager
*/

#ifndef R_TYPE_SCORE_MANAGER_HPP_
#define R_TYPE_SCORE_MANAGER_HPP_

#include "Components/Text.hpp"

class ScoreManager {
    static inline constexpr char const *HIGHSCORE_FILE = "rtype-highscore.txt";

public:
    ScoreManager(Component::Text &scoreText);
    ~ScoreManager();
    void addScore(int score);

private:
    Component::Text &_scoreText;
    int _score;
    int _highscore;
};

#endif /* !R_TYPE_SCORE_MANAGER_HPP_ */
