#include "pch.h"
#include "StaticGraphicElement.h"
extern  SDL_Window* myWindow;//������� ����

extern  SDL_Renderer* myRenderer;

StaticGraphicElement::StaticGraphicElement(): GraphicElement()
{

}


StaticGraphicElement::~StaticGraphicElement()
{
	free();
}
bool StaticGraphicElement::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();
	
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
//
//void StaticGraphicElement::free() 
//{
//	//Free texture if it exists
//	if (mTexture != NULL)
//	{
//		SDL_DestroyTexture(mTexture);
//		mTexture = NULL;
//		mWidth = 0;
//		mHeight = 0;
//	}
//}

//
//void StaticGraphicElement::setBlendMode(SDL_BlendMode blending)
//{
//	//Set blending function
//	SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//void StaticGraphicElement::setAlpha(Uint8 alpha)
//{
//	//Modulate texture alpha
//	SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//void StaticGraphicElement::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
//{
//	//Set rendering space and render to screen
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//	//Set clip rendering dimensions
//	if (clip != NULL)
//	{
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	//Render to screen
//	SDL_RenderCopyEx(myRenderer, mTexture, clip, &renderQuad, angle, center, flip);
//}
//
