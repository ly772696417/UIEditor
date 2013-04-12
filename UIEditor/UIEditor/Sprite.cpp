#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	D3DXCreateSprite(m_pD3DDevice,&spriteobj);
}


Sprite::~Sprite(void)
{
}

void Sprite::PrintText(string text,int x,int y,string font /* = "Arial Bold" */,int fontSize /* = 30 */,D3DCOLOR color /* = D3DCOLOR_XRGB */)
{
	m_font = this->MakeFont(font,fontSize);

	spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
	this->FontPrint(m_font,x,y,text);
	spriteobj->End();
}

void Sprite::PrintSprite(string filename,int x,int y,int width,int height,D3DCOLOR transcolor)
{
	m_texture = this->LoadTexture(filename,transcolor);
	spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
	this->Sprite_Transform_Draw(m_texture,x,y,width,height);
	spriteobj->End();
}


LPD3DXFONT Sprite::MakeFont(string name,int size)
{
	LPD3DXFONT font = NULL;

	D3DXFONT_DESC desc = {
		size,                   //height
		0,                      //width
		0,                      //weight
		0,                      //miplevels
		false,                  //italic
		DEFAULT_CHARSET,        //charset
		OUT_TT_PRECIS,          //output precision
		CLIP_DEFAULT_PRECIS,    //quality
		DEFAULT_PITCH,          //pitch and family
		""                      //font name
	};

	strcpy_s(desc.FaceName, name.c_str());

	D3DXCreateFontIndirect(m_pD3DDevice, &desc, &font);

	return font;
}

void Sprite::FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color)
{
	//figure out the text boundary
	RECT rect = { x, y, 0, 0 };
	font->DrawText( NULL, text.c_str(), text.length(), &rect, DT_CALCRECT, color); 

	//print the text
	font->DrawText(spriteobj, text.c_str(), text.length(), &rect, DT_LEFT, color); 
}

void Sprite::Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, 
								   int x, int y, int width, int height, 
								   int frame /* = 0 */, int columns /* = 1 */, 
								   float rotation /* = 0.0f */, 
								   float scaleW /* = 1.0f */, float scaleH /* = 1.0f */, 
								   D3DCOLOR color /* = D3DCOLOR_XRGB */)
{
	//create a scale vector
	D3DXVECTOR2 scale( scaleW, scaleH );

	//create a translate vector
	D3DXVECTOR2 trans( (float)x, (float)y );

	//set center by dividing width and height by two
	D3DXVECTOR2 center( (float)( width * scaleW )/2, (float)( height * scaleH )/2);

	//create 2D transformation matrix
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D( &mat, NULL, 0, &scale, &center, rotation, &trans );

	//tell sprite object to use the transform
	spriteobj->SetTransform( &mat );

	//calculate frame location in source image
	int fx = (frame % columns) * width;
	int fy = (frame / columns) * height;
	RECT srcRect = {fx, fy, fx + width, fy + height};

	//draw the sprite frame
	spriteobj->Draw( image, &srcRect, NULL, NULL, color );


	//added in chapter 14
	D3DXMatrixIdentity( &mat );
	spriteobj->SetTransform( &mat );
}


LPDIRECT3DTEXTURE9 Sprite::LoadTexture(string filename, D3DCOLOR transcolor)
{  
	LPDIRECT3DTEXTURE9 texture = NULL;

	//get width and height from bitmap file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) return NULL;

	//create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx( 
		m_pD3DDevice,                //Direct3D device object
		filename.c_str(),      //bitmap filename
		info.Width,            //bitmap image width
		info.Height,           //bitmap image height
		1,                     //mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,       //the type of surface (standard)
		D3DFMT_UNKNOWN,        //surface format (default)
		D3DPOOL_DEFAULT,       //memory class for the texture
		D3DX_DEFAULT,          //image filter
		D3DX_DEFAULT,          //mip filter
		transcolor,            //color key for transparency
		&info,                 //bitmap file info (from loaded file)
		NULL,                  //color palette
		&texture );            //destination texture

	//make sure the bitmap textre was loaded correctly
	if (result != D3D_OK) return NULL;

	return texture;
}
