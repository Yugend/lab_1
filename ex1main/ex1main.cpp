// ex1main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SDL.h>
#include <cstdlib>
#include <iostream>

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char**) {
	std::cout << "Begin main" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Hello World!", 0, 30, 640, 480, SDL_WINDOW_SHOWN);
	if (win == 0) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	SDL_Window* win1 = SDL_CreateWindow("Hello World!", 890, 340, 640, 480, SDL_WINDOW_SHOWN);
	if (win1 == 0) {
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

	SDL_Renderer* ren1 = SDL_CreateRenderer(win1, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (win1 == 0) {
		SDL_DestroyWindow(win1);
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

	std::string imagePath1 = ".\\welcome.bmp";
	SDL_Surface* bmp1 = SDL_LoadBMP(imagePath1.c_str());
	if (bmp1 == 0) {
		SDL_DestroyWindow(win1);
		SDL_DestroyRenderer(ren1);
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

	SDL_Texture* tex1 = SDL_CreateTextureFromSurface(ren1, bmp1);
	SDL_FreeSurface(bmp1);
	if (tex1 == 0) {
		SDL_DestroyWindow(win1);
		SDL_DestroyRenderer(ren1);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
	}

	for (int i = 0; i < 10; i++) {
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
		SDL_Delay(100);
	}

	SDL_Rect dst1;
	dst1.x = 0;
	dst1.y = 0;
	dst1.w = 640;
	dst1.h = 480;
	for (int i = 0; i < 100; i++) {
		SDL_RenderClear(ren1);
		dst1.x = -10 * i;
		dst1.y = -5 * i;
		SDL_RenderCopy(ren1, tex1, NULL, &dst1);
		SDL_RenderPresent(ren1);
		SDL_Delay(100);
	}


	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_DestroyTexture(tex1);
	SDL_DestroyRenderer(ren1);
	SDL_DestroyWindow(win1);

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
