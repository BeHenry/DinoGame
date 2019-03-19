#include "Game.h"

#include "Gamepadneural.h"
#include "Watchneural.h"
#include "GamepadPlayer.h"
 
#include <iostream>
#include <fstream>
#include "string.h"
#include <SDL2/SDL.h>
#include "aux/Matrix.h"
#include "aux/NeuralNetwork.h"
#include "Afficheur.h"


void initializeAssets(SDL_Texture* text, Afficheur* aff);
int play(Game* jeu);
void train();
void run(int gen)
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	
	SDL_Window* fenetre =  SDL_CreateWindow("test de la SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 500, SDL_WINDOW_SHOWN);
	
	if(fenetre == 0)
	{
		std::cout << "Erreur lors de l'initialisation de la fenêtre: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	SDL_Renderer* rend = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	if(rend == NULL)
	{
		std::cout << "Erreur lors de l'initialisation de la fenêtre: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderPresent(rend);
	// Load main assets file
	SDL_Surface* temp_a = IMG_Load("data/assets.png");
	SDL_Texture* assets = SDL_CreateTextureFromSurface(rend,temp_a);
	SDL_FreeSurface(temp_a);
	// Create Assets dictionary
	Gamepadneural pad = Gamepadneural("data/generation"+std::to_string(50)+".nn", &atan);
	GamepadPlayer padP = GamepadPlayer();
	Afficheur mainAff = Afficheur(rend, 0, 0);
	Afficheur affPlayer = Afficheur(rend, 0, 200);
	initializeAssets(assets,&mainAff);
	initializeAssets(assets,&affPlayer);
	Game jeu = Game(&pad);
	Game jeu2 = Game(&padP);
	bool terminer, terminer2 = false;
	bool endall = true;
	int count, count2=0;
	int seed;
	SDL_Event ev;
	SDL_RenderClear(rend);
	mainAff.affichage(&jeu,count);
	affPlayer.affichage(&jeu2,count);
	SDL_RenderPresent(rend);
	while(endall)
	{
		
		if((!terminer) or (!terminer2))
		{
			seed=rand();
			if(!terminer)
			{
				srand(seed);
				terminer =  jeu.frameUpdate();
				count = count + 1;
			}
			SDL_RenderClear(rend);
			
			
			
			if(!terminer2)
			{
				srand(seed);
				terminer2 = jeu2.frameUpdate();
				count2 = count2 +1;
			}
			mainAff.affichage(&jeu,count);
			affPlayer.affichage(&jeu2,count2);
			SDL_RenderPresent(rend);
			SDL_Delay(5);
		}
		else
		{
			
			SDL_WaitEvent(&ev);
			if(ev.type==SDL_QUIT)
			{
				endall = false;
			}
			else if(ev.type==SDL_KEYDOWN)
			{
				jeu.reinit();
				jeu2.reinit();
				terminer = false;
				terminer2 = false;
			}
		}
		
		
		
		
	}
	SDL_DestroyTexture(assets);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	
	
}
int main()
{
	/*srand(time(NULL));
	int gen ;
	std::cin >> gen;
	run(gen);*/
	train();
	return 0;
}
int play(Game* jeu)
{
	jeu->reinit();
	bool terminer = false;
	int count=0;
	while((!terminer))
	{
		terminer = jeu->frameUpdate();
		
		count += 1;
		
		
	}
	return count;
}
void initializeAssets(SDL_Texture* text, Afficheur* aff)
{
	SDL_Rect rect;
	SDL_Rect rect2;
	// Create Dino asset
	rect.x=1850;
	rect.y=0;
	rect.h=100;
	rect.w=90;
	rect2.x=150;
	rect2.y=0;
	rect2.w=rect.w/2;
	rect2.h=rect.h/2;
	Asset dino1 = Asset(rect, text, 0);
	
	rect.x=1940;
	dino1.addAnimationFrame(rect);
	dino1.setAnimationOffset(20);
	aff->addAsset(dino1, rect2);
	
	// Create Cactus asset
	rect.x=804;
	rect.w=50;	
	rect.h=100;
	rect2.w=rect.w/2;
	rect2.h=rect.h/2;
	Asset cactus = Asset(rect, text, 1);
	aff->addAsset(cactus, rect2);
	//Create cactus small$
	rect.x=445;
	rect.y=1;
	rect.h=72;
	rect.w=35;
	rect2.w=rect.w/2;
	rect2.h=rect.h/2;
	Asset cactusXL = Asset(rect, text, 2);
	aff->addAsset(cactusXL, rect2);
	
	//create ptero
	
	rect.x=259;
	rect.y=13;
	rect.h=71;
	rect.w=95;
	rect2.x=150;
	rect2.y=0;
	rect2.w=rect.w/2;
	rect2.h=rect.h/2;
	Asset ptero1 = Asset(rect, text, 3);
	
	rect.x=355;
	rect.y=13;
	rect.h=80;
	rect.w=94;
	ptero1.addAnimationFrame(rect);
	ptero1.setAnimationOffset(20);
	aff->addAsset(ptero1, rect2);
	// Create ground asset
	rect.h=30;
	rect.w=2250;
	rect.y=100;
	rect.x=0;
	rect2.x=0;
	rect2.y=140;
	rect2.w=rect.w/2;
	rect2.h=rect.h/2;
	Asset ground = Asset(rect, text, 4);
	aff->addAsset(ground, rect2);
	

}
void train()
{
	
	int result, n_selec, ind_max = -1;
	int res2;
	float max;
	
	
	bool flag;
	float u;
	float p =0.3;
	flag = true;
	bool terminer = false;
	bool is_selected;
	int p1, p2;
	int total = 0;
	int N_ind = 100;
	int N_gen = 2000;
	int N_selec = 20;
	int index_selec[N_selec];
	float scores_selec[N_selec];
	Gamepadneural* pads = new Gamepadneural[N_ind];
	pads[0].save("data/generation"+std::to_string(0)+".nn");
	//Gamepad* mouse = new GamepadPlayer();
	int dim;
	
	dim = pads[0].getDim();
	
	Matrix new_weight = Matrix(dim,1);
	Matrix m = Matrix(dim,1);
	
	Matrix M = indentity(dim);
	Matrix chol = M.cholesky(&flag);
	int count = 1;
	int selected;
	
	
	float scores[N_ind];
	
	bool first;
	for(int i = 0; i < N_ind; i++)
	{
		scores[i] = 0;		
		pads[i].sampleWeights(&chol,&m);
	}
	
	
	
	Game jeu = Game(&pads[0]);
	for(int K = 0; K < N_gen; K++)
	{
		total = 0;
		for(int i = 0; i < N_ind; i++)
		{
				
				jeu.setPads(&pads[i]);
				jeu.reinit();
				result = play(&jeu);
				scores[i] = result;

		}
		//SELECTION DES INDIVIDUS
		first = true;
		for(int i = 0; i < N_selec; i++)
		{
			index_selec[i]=0;
			max = -1;
			ind_max = -1;
			for(int j = 0; j < N_ind; j++)
			{
				if(scores[j] >= max)
				{
					max = scores[j];
					ind_max = j;
					
					
				}
				
			}
			index_selec[i] = ind_max;
			//std::cout << "Ind:" << ind_max << " " <<"score:" << scores[ind_max] << " //  " ;
			scores_selec[i]=scores[ind_max];
			total = total +max;
			scores[ind_max] = -2;
			
			
		}
		std::cout << "Generation " << K << ": " << (float)total/(float)N_selec << std::endl;
		std::cout << std::endl;
		
		
		pads[index_selec[0]].save("data/generation"+std::to_string(K+1)+".nn");
		
		
		/*jeu.reinit();
		jeu.setPads(&pads[index_selec[0]]);
		count = 1;
		while((!terminer))
		{
			terminer = jeu.frameUpdate();
			mainAff.affichage(&jeu,count);
			count += 1;
		
		
		}
		terminer = false;*/
		/*jeu.reinit();
		jeu.setPads(mouse);
		while((!terminer))
		{
			terminer = jeu.frameUpdate();
			mainAff.affichage(&jeu,count);
			count += 1;
		
		
		}
		terminer = false;*/
		//pads[index_selec[0]].changeWeight(pads[index_selec[0]].getWVec());
		//jeu.setPads(&pads[index_selec[0]]);
		//jeu.reinit();
		
		
		
		for(int i = 0; i < N_ind; i++)
		{
			is_selected = false;
			for(int j = 0; j < N_selec; j++)
			{
				if(i==index_selec[j])
				{
					is_selected = true;
				}
			}
			if(!is_selected)
			{
				u=(float)rand()/(float)RAND_MAX;
				p1 = rand() % N_selec;
				p2 = rand() % N_selec;
				if(u>p)
				{
					new_weight=pads[index_selec[p1]].getWVec();//mixing(pads[index_selec[p1]].getWVec(),pads[index_selec[p2]].getWVec(),scores_selec[p1],scores_selec[p2]);
					pads[i].changeWeight(new_weight);
					pads[i].Mutation();
				}
				else if(u<0.95)
				{
					new_weight=mixing(pads[index_selec[p1]].getWVec(),pads[index_selec[p2]].getWVec(),scores_selec[p1],scores_selec[p2]);
					pads[i].changeWeight(new_weight);
				}
				else
				{
					pads[i].sampleWeights(&chol,&m);
				}
			}
		}
		
		
	}
	
	delete[] pads;
	
}
/*int main(int argc, char *argv[])
{
	
	
	int result, n_selec, ind_max;
	int res2;
	float max;
	Matrix m = Matrix(35,1);
	Matrix int_m = Matrix(35,1);
	Matrix M = indentity(35);
	Matrix int_M = Matrix(35,35);
	bool flag;
	float u;
	float p =0.5;
	flag = true;
	bool is_selected;
	int p1, p2;
	Matrix chol = M.cholesky(&flag);
	int N_ind = 500;
	int N_gen = 200 ;
	int N_selec = 10;
	int index_selec[N_selec];
	float scores_selec[N_selec];
	Matrix new_weight = Matrix(35,1);
	
	int selected;
	Watchneural* watch = new Watchneural;
	
	Gamepadneural* pads = new Gamepadneural[N_ind];
	
	float scores[N_ind];
	
	bool first;
	for(int i = 0; i < N_ind; i++)
	{
		scores[i] = 0;		
		pads[i].sampleWeights(&chol,&m);
	}
	
	Game jeu = Game(&pads[0]);
	for(int K = 0; K < N_gen; K++)
	{
		for(int i = 0; i < N_ind; i++)
		{
				
				jeu.setPads(&pads[i]);
				jeu.reinit();
				result = jeu.play();
				scores[i] = result;

		}
		//SELECTION DES INDIVIDUS
		first = true;
		for(int i = 0; i < N_selec; i++)
		{
			index_selec[i]=0;
			max = -1;
			ind_max = -1;
			for(int j = 0; j < N_ind; j++)
			{
				if(scores[j] >= max)
				{
					max = scores[j];
					ind_max = j;
					
					
				}
			}
			index_selec[i] = ind_max;
			std::cout << "Ind:" << ind_max << " " <<"score:" << scores[ind_max] << " //  " ;
			scores_selec[i]=scores[ind_max];
			scores[ind_max] = -2;
			
			
		}
		std::cout << std::endl;
		
		
		watch->changeWeight(pads[index_selec[0]].getWVec());
		jeu.setPads(watch);
		
		
		jeu.reinit();
		res2 = jeu.play();
		//pads[index_selec[0]].changeWeight(pads[index_selec[0]].getWVec());
		//jeu.setPads(&pads[index_selec[0]]);
		//jeu.reinit();
		std::cout << "score selec:" << res2 << std::endl;
		std::cout << "selec with gamped:" << scores_selec[0] << std::endl;
		
		for(int i = 0; i < N_ind; i++)
		{
			is_selected = false;
			for(int j = 0; j < N_selec; j++)
			{
				if(i==index_selec[j])
				{
					is_selected = true;
				}
			}
			if(!is_selected)
			{
				u=(float)rand()/(float)RAND_MAX;
				p1 = rand() % N_selec;
				p2 = rand() % N_selec;
				if(u>p)
				{
					new_weight=pads[index_selec[p1]].getWVec();//mixing(pads[index_selec[p1]].getWVec(),pads[index_selec[p2]].getWVec(),scores_selec[p1],scores_selec[p2]);
					pads[i].changeWeight(new_weight);
					pads[i].Mutation();
				}
				else if(u<0.98)
				{
					new_weight=mixing(pads[index_selec[p1]].getWVec(),pads[index_selec[p2]].getWVec(),scores_selec[p1],scores_selec[p2]);
					pads[i].changeWeight(new_weight);
				}
				else
				{
					pads[i].sampleWeights(&chol,&m);
				}
			}
		}
		
		jeu.newObstacle();
	}
	
	delete[] pads;
	delete watch;
	
	return 0;
}


*/
