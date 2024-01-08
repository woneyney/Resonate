/*
*GAM100
*Dohyung Kwon, Gyuwon Na, Deokwoo Seo
*All content © 2023 DigiPen(USA) Corporation, all rights reserved.
*/

#include "Setting.h"

AttackBoss attackboss;
AttackPlayer attackplayer;
BackGround background;
Boss boss;
Credit credit;
DrawBoss drawboss;
DrawPlayer drawplayer;
GameSetting setting;
Heart heart;
PlayerHeart playerheart;
BossHeart bossheart;
DigiPen digipen;
StarLink team;
Pattern1 pattern1;
Stone pattern2;
ShockWave pattern3;
Player player;
Potion potion;
Home home;

int state;
float timePlayed = 0.0f;

void load()
{
	digipen.load();
	team.load();
	background.load();
	heart.load();
	drawboss.load();
	drawplayer.load();
	credit.load();
	setting.load();
	pattern1.load();
	pattern2.load();
	pattern3.load();
	potion.load();
	home.load();
}

void unload()
{
	digipen.unload();
	team.unload();
	background.unload();
	heart.unload();
	credit.unload();
	drawboss.unload();
	drawplayer.unload();
	setting.unload();
	pattern1.unload();
	pattern2.unload();
	pattern3.unload();
	potion.unload();
	home.unload();
}

void game()
{
	if (player.MovingPosition.y >= boss.position.y + (boss.height - player.height)) //to consider a sense of distance
	{
		drawboss.draw_Moving();
		drawboss.draw_Attacking();
		drawplayer.draw_Moving();
		drawplayer.draw_Attacking();
	}
	else
	{
		drawplayer.draw_Moving();
		drawplayer.draw_Attacking();
		drawboss.draw_Moving();
		drawboss.draw_Attacking();
	}
	MovingCollide();
	attackboss.attack();
	attackplayer.attack();
	boss.Moving();
	player.Moving();
	pattern1.pattern1();
	pattern2.pattern2();
	pattern3.pattern3();
	heart.draw();
	potion.draw();
	home.EndWhenYouLose();
	home.EndWhenYouWin();
}

int main()
{
	srand((unsigned int)time(NULL));
	InitWindow(window_width, window_height, "Resonate");
	InitAudioDevice();

	SetTargetFPS(windows_per_frame_second);

	Music bg1 = LoadMusicStream("musics/BGM_part1.mp3");
	Music bg2 = LoadMusicStream("musics/BGM_part2.mp3");
	Sound sword = LoadSound("musics/sword.mp3");

	load();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		digipen.draw();
		background.draw();
		team.draw();

		if (UnloadDigiPenLogo && UnloadTeamLogo)
		{
			switch ((State)state)
			{
			case State::main:
				home.draw();
				break;

			case State::start:
				game();

				PlayMusicStream(bg1);
				UpdateMusicStream(bg1);
				timePlayed = (GetMusicTimePlayed(bg1) / GetMusicTimeLength(bg1));
				if (timePlayed > 1.0f)
				{
					timePlayed = 0.0f;
				}
				if (PlayerIsAttacking)
				{
					PlaySound(sword);
				}
				if (bgmchange)
				{
					StopMusicStream(bg1);
					PlayMusicStream(bg2);

					UpdateMusicStream(bg2);
					timePlayed = (GetMusicTimePlayed(bg2) / GetMusicTimeLength(bg2));
					if (timePlayed > 1.0f)
					{
						timePlayed = 0.0f;
					}
				}

				if (Lose || Win)
				{
					player.speed = 0;
					player.upspeed = 0;
					player.diagonalSpeed = 0;
					boss.speed = 0;

					PlayerIsAttacking = false;
					BossIsAttacking = false;
					ShieldExecuted = false;

					StopMusicStream(bg1);
					StopMusicStream(bg2);
					StopSound(sword);
				}
				if (IsKeyPressed(KEY_F1)) //change game mode into cheat mode
				{
					state = 3;
				}
				break;

			case State::exit:
				break;

			case State::cheat:
				game();

				PlayMusicStream(bg1);
				UpdateMusicStream(bg1);
				timePlayed = (GetMusicTimePlayed(bg1) / GetMusicTimeLength(bg1));
				if (timePlayed > 1.0f)
				{
					timePlayed = 0.0f;
				}
				if (PlayerIsAttacking)
				{
					PlaySound(sword);
				}
				if (bgmchange)
				{
					StopMusicStream(bg1);
					PlayMusicStream(bg2);

					UpdateMusicStream(bg2);
					timePlayed = (GetMusicTimePlayed(bg2) / GetMusicTimeLength(bg2));
					if (timePlayed > 1.0f)
					{
						timePlayed = 0.0f;
					}
				}

				if (Win)
				{
					player.speed = 0;
					player.upspeed = 0;
					player.diagonalSpeed = 0;
					boss.speed = 0;

					PlayerIsAttacking = false;
					BossIsAttacking = false;
					ShieldExecuted = false;

					StopMusicStream(bg1);
					StopMusicStream(bg2);
					StopSound(sword);
				}
				if (IsKeyPressed(KEY_F1)) //change cheat mode into game mode
				{
					state = 1;
				}
				break;

			case State::setting:
				setting.draw();
				break;

			case State::credit:
				credit.draw();
				break;
			}
		}

		if (state == 2)
			break;

		EndDrawing();
	}

	UnloadMusicStream(bg1);
	UnloadMusicStream(bg2);
	UnloadSound(sword);
	unload();
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
