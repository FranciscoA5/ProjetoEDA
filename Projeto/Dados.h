/**
* @file Dados.h
* @author Francisco Andrade
* @email f-infsec03@hotmail.com
* @date 1/04/2022
* @brief  Definições Globais para Lista Ligadas Simples
*/

#ifndef Dados
#define Dados 1
#define MAX 11
#define MAX1 100
#define M 4		
#define T 10

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#pragma warning( disable : 4996 )//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS


#pragma region Estruturas
typedef struct Maquina {
	int num, unitempo;
	struct Maquina* next;

}Maquina;

typedef struct Operacao {
	int cod;
	Maquina* listamaquinas;
	struct Operacao* next;

}Operacao;

typedef struct Job {
	char* id;
	Operacao* listaOperacoes;
	struct Job* next;

}Job;

#pragma endregion


#pragma region HashTable

void IniciaHash(Job* hashTable[]);
int Key(char* id);
void InsereNodoJobNaHash(Job* job, Job* hashTable[]);
void RemoveJobNaHash(char* id, Job* hashTable[]);
void MostrarHashTable(Job* hashTable[]);

#pragma endregion

#pragma region Jobs

Job* CriaJob(char* id);
Job* InsereJob(Job* jobsHeader, Job* novoJob);
void MostraListaJobs(Job* jobsHeader);

#pragma endregion


#pragma region Maquinas
Maquina* criaMaquina(int num, int unitempo);
Maquina* insereMaquina(Maquina* h, Maquina* novamaquina);
Maquina* procuraMaquina(Operacao* h, int cod, int num);
void alteraMaquina(Maquina* h, int num, int cod, int novonum, int novounitempo);
void MostraListaMaquinas(Maquina* maquinasHeader);

#pragma endregion

#pragma region Operacao
Operacao* criaOperacao(int cod);
Operacao* procuraOperacao(Operacao* h, int cod);
//Operacao* RemoveOperacao(Operacao* h, int cod);
Operacao* minTempo(Operacao* headoperacao, int* soma);
Operacao* maxTempo(Operacao* headoperacao, int* soma);
Operacao* removeOperacaoRecursivo(Operacao* h, int cod);
Operacao* insereOperacaoOrdenada(Operacao* h, Operacao* novaoperacao);
float media(Operacao* headoperacao, int cod);
int contaOperacoes(Operacao* h);
void MostraListaOperacoes(Operacao* operacoesHeader);


#pragma endregion

#pragma region Ficheiros

void lerFicheiros(FILE* fp, char nome[100]);
void escreverFicheiros(Operacao* h, FILE* fp, char nome[100]);

#pragma endregion

#pragma region Planeamento
typedef struct Cel {
	int idJob;
	int idOper;
	//tempo
	//outras
} Cel;

void IniciaPlano(Cel p[][T], int codJob, int codOper);
void OcupaUm(Cel p[][T], int mId, int t, int codJob, int codOper);
void OcupaVarios(Cel p[][T], int mId, int totTempo, Cel* c);
void Ocupa(Cel p[][T], int mId, int totTempo, int codJ, int codO);

bool SavePlan(char* fileName, Cel p[][T]);
Cel** GetPlan(char* fileName);

#pragma endregion

#endif
