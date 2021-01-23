// ex2main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <cstdlib>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char**) {
	std::cout << "Begin main" << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Hello World!", 50, 50, 640, 480, SDL_WINDOW_SHOWN);
	if (win == 0) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (win == 0) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	std::string imagePath = ".\\hello.bmp";
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == 0) {
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == 0) {
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
		system("PAUSE");
		exit(2);
	}
	TTF_Font* font;
	font = TTF_OpenFont("CharisSILR.ttf", 26);
	if (!font) {
		std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
		system("PAUSE");
	}


	for (int i = 0; i < 5; i++) {
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
		SDL_Delay(10);
	}

	SDL_Window* win2 = SDL_CreateWindow("Hello World!", 800, 300, 640, 480, SDL_WINDOW_SHOWN);
	if (win == 0) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (win == 0) {
		SDL_DestroyWindow(win2);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == 0) {
		SDL_DestroyWindow(win2);
		SDL_DestroyRenderer(ren2);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Color color = {0, 0, 0};
	SDL_Surface* text_surface;
	if (!(text_surface = TTF_RenderUNICODE_Blended(font, reinterpret_cast<Uint16 const*>(L"Здравствуйте всем, привет всем!"), color))) {
		system("PAUSE");
	}
	else
	{
		SDL_BlitSurface(text_surface, NULL, bmp, NULL);
		SDL_FreeSurface(text_surface);
	}
	SDL_Texture* tex2 = SDL_CreateTextureFromSurface(ren2, bmp);
	SDL_FreeSurface(bmp);
	if (tex2 == 0) {
		SDL_DestroyWindow(win2);
		SDL_DestroyRenderer(ren2);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}


	SDL_Rect dst;
	SDL_Rect dst2;
	dst.x = 0;
	dst.y = 0;
	dst.w = 640;
	dst.h = 480;
	dst2.x = 0;
	dst2.y = 0;
	dst2.w = 640;
	dst2.h = 480;
	int i = 0, dirs = 1;

	SDL_Event e;
	SDL_MouseButtonEvent e1;
	bool quit1 = false, quit2 = false, flag1 = false, flag2 = false;
	while (!quit1 || !quit2) {
		if (quit1)
		{
			SDL_DestroyRenderer(ren);
			SDL_DestroyWindow(win);
		}
		if (quit2)
		{
			SDL_DestroyRenderer(ren2);
			SDL_DestroyWindow(win2);
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_a)
					flag1 = true;
				else if (e.key.keysym.sym == SDLK_b && flag1)
					quit1 = true;
				else if (e.key.keysym.sym == SDLK_c)
					flag2 = true;
				else if (e.key.keysym.sym == SDLK_d && flag2)
					quit2 = true;
				else { flag1 = false; flag2 = false; }
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT)
					quit1 = true;
				if (e.button.button == SDL_BUTTON_RIGHT)
					quit2 = true;
			}
		}
		i += dirs;
		if (i > 10)
			dirs = -1;
		if (i < 0)
			dirs = +1;
		SDL_RenderClear(ren);
		dst.x = 10 * i;
		dst.y = 5 * i;
		SDL_RenderCopy(ren, tex, NULL, &dst);
		SDL_RenderPresent(ren);
		SDL_RenderClear(ren2);
		dst2.x = -10 * i;
		dst2.y = -5 * i;
		SDL_RenderCopy(ren2, tex2, NULL, &dst2);
		SDL_RenderPresent(ren2);
		SDL_Delay(100);
	}
	TTF_Quit();

	SDL_DestroyTexture(tex);

	std::cout << "End main before SDL_Quit" << std::endl;
	SDL_Quit();
	std::cout << "End main after SDL_Quit" << std::endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
