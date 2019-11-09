#include "text.h"

void displayMessage(char* message, tuple pos, int color)
{
    for(int i=0; i < strlen(message); i++)
    {
        char l = message[i];
        if (l == ' ')
        {
            afficheSprite(spr_space, pos.x, pos.y, color);
            pos.x += 6*RATIO;
        }
        else if(l=='?')
        {
            afficheSprite(spr_interrogation, pos.x, pos.y, color);
            pos.x += 6*RATIO;
        }
        else if(l=='0')
        {
            afficheSprite(*numbers[0], pos.x, pos.y, color);
            pos.x += 6*RATIO;
        }

        else if(l=='1' || l=='2' || l=='3' || l=='4' || l=='5' ||l=='6' || l=='7' || l=='8' || l=='9')
        {
            afficheSprite(*numbers[l-'0'], pos.x, pos.y, color);
            pos.x += 5*RATIO;
        }

        else
        {
            afficheSprite(*alphabet[l-'A'], pos.x, pos.y, color);
            pos.x += 8*RATIO;
        }
    }
}

void displayGameOver(tuple* text_pos)
{
    displayMessage("GAME", *text_pos, RED);
    text_pos->y += 40;
    displayMessage("OVER", *text_pos, RED);
    text_pos->y -= 40;
    if (text_pos->y < 70)
        text_pos->y += 4;
    if (game.update_rate < 300)
        game.update_rate += 2;
}

void displayWaveNum(tuple* wave_text_pos, int* wave_text_speed, t_boss* boss)
{
    char msg[20];
    if (game.background_scroll_speed < 10)
        game.background_scroll_speed = 10;

    if (wave_text_pos->x > -200) {
        if (game.current_wave->boss_id) {
            if (boss->triggered) {
                if (wave_text_pos->x >= 45 && wave_text_pos->x < 100)
                    *wave_text_speed = 2;
                else
                    *wave_text_speed = 40;

                displayMessage("THE BOSS", *wave_text_pos, game.counter % 8 + 2);
                wave_text_pos->y += 40;
                displayMessage("IS ANGRY", *wave_text_pos, game.counter % 8 + 2);
                wave_text_pos->y -= 40;
                wave_text_pos->x -= *wave_text_speed;
            }
        } else {
            if (game.current_wave->index == FAKE_END) {
                if (wave_text_pos->x >= 45 && wave_text_pos->x < 100)
                    *wave_text_speed = 2;
                else
                    *wave_text_speed = 40;
                displayMessage("FINAL WAVE", *wave_text_pos, RED);
            } else {
                if (wave_text_pos->x > 90 && wave_text_pos->x <= 130)
                    *wave_text_speed = 2;
                else
                    *wave_text_speed = 40;
                sprintf(msg, "WAVE %d", game.current_wave->index);
                displayMessage(msg, *wave_text_pos, WHITE);
            }
            wave_text_pos->x -= *wave_text_speed;
        }
    }
    else {
        game.background_scroll_speed = 2;
        game.show_wave_nb = 0;
        wave_text_pos->x = 400;
    }
}