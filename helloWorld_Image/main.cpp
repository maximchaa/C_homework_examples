#include <iostream>
#include <SDL2/SDL.h> //Подключение заголовочного файла SDL
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;  //Объявим пару константных значений для ширины и высоты экрана
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;  //Глобальное объявление окна и рендера
SDL_Renderer *renderer = NULL;

//Объявление функции для загрузки текстур по имени файла
//С ее помощью мы можем передать имя файла как строчку и получить указатель на загруженную текстуру
SDL_Texture* LoadImage(std::string file)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL){
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        cout << SDL_GetError() << endl;
    return texture;
}

//Объявление функции для упрощения рисования
//Позволяет указывать позицию изображения на экране
//Будет принимать x и y координаты, указатели на текстуру и рендерер и рисовать текстуру в указанной точке
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(rend, tex, NULL, &pos);
}

int main(int argc, const char * argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  //Инициализация всех подсистем SDL
    {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    window = SDL_CreateWindow("Lesson 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Создание окна для отображения на рендер
    //SDL_WINDOWPOS_CENTERED позволяет при создании окна отцентровать его по определенной оси, в данном случае отцентрирование по x, так и по y.
    if (window == NULL)
    {
        cout << SDL_GetError() << endl;
        return 2;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Создание рендера, чтобы иметь возможность рисовать в окне
    if (renderer == NULL)
    {
        cout << SDL_GetError() << endl;
        return 3;
    }
    
    //Загрузим картинки с помощью LoadImage функции
    SDL_Texture *background = NULL, *image = NULL;
    background = LoadImage("/Applications/Maximchaa/INBOX/background.bmp");
    image = LoadImage("/Applications/Maximchaa/INBOX/image.bmp");
    if (background == NULL || image == NULL)
        return 4;
    
    SDL_RenderClear(renderer);  //Очистка рендера
    
    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    ApplySurface(0, 0, background, renderer);
    ApplySurface(bW, 0, background, renderer);
    ApplySurface(0, bH, background, renderer);
    ApplySurface(bW, bH, background, renderer);
    
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    ApplySurface(x, y, image, renderer);
    
    SDL_RenderPresent(renderer);  //Показ обновленного экрана, чтобы увидеть результат
    SDL_Delay(10000);  //Оставить окно открытым на 10 секунд
    
    return 0;
}
