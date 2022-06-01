/**
* @file Funcoes.c
* @author Francisco Andrade
* @email f-infsec03@hotmail.com
* @date 1/04/2022
* @brief Metodos para manipular Listas Ligadas Simples
*/

#include"Dados.h"

#pragma region Funcoes


#pragma region HashTable

/**
* Inicia o ínicio de uma nova hash table
* @param [in] hashTable
*/
void IniciaHash(Job* hashTable[]) {
	for (int i = 0; i < MAX; i++) {
		hashTable[i] = NULL; //é o mesmo que ter as linhas de codigo em baixo
		// hashTable[i]->id = NULL;
		// hashTable[i]->nextJob = NULL;
		// hashTable[i]->operacoes = NULL;
	}
}

/**
* Determina a key necessária para inserir na hash table
* @param [in] id
* @param [out] key    //Retorna a key
*/
int Key(char* id) {
	int soma = 0;
	for (int i = 0; i < strlen(id); i++) {
		soma += (int)id[i];
	}
	return soma % MAX;
}


/**
	 * Insere o nodo Job recebido no incio da hash table
	 * @param [in] job
	 * @param [in] hashTable
	*/
void InsereNodoJobNaHash(Job* job, Job* hashTable[]) {
	int key = Key(job->id);
	job->next = hashTable[key]; //o proximo job que sera nulo em principio vai apontar para o inicio da HasTable
	hashTable[key] = job;
}

/**
 * Remover o Job
 * @param [in] id
 * @param [in] jobsHeader
*/
void RemoveJobNaHash(char* id, Job* hashTable[]) {
	int key = Key(id);
	if (hashTable[key] == NULL) return;

	if (strcmp(hashTable[key]->id, id) == 0) { //remove no inicio da lista
		Job* auxJob = hashTable[key];
		hashTable[key] = hashTable[key]->next;
		free(auxJob);
	}
	else {
		Job* auxJob = hashTable[key];
		Job* auxAnt = auxJob;
		while (auxJob && strcmp(auxJob->id, id) > 0) { //procura para remover
			auxAnt = auxJob;
			auxJob = auxJob->next;
		}
		if (auxJob != NULL) { //se encontrou, remove
			auxAnt->next = auxJob->next;
			free(auxJob);
		}
	}
}

/**
* Mostra a lista de jobs e operações e máquinas usando a hash table
* @param [in] hashTable
*/
void MostrarHashTable(Job* hashTable[]) {
	for (int i = 0; i < MAX; i++) {
		if (hashTable[i] != NULL) {
			printf("Index: %d\n", i);
			MostraListaJobs(hashTable[i]);
			printf("\n");
		}
	}
}

#pragma endregion 

#pragma region Jobs

/**
	 * Cria um job
	 * @param [in] id
	 * @param [in] operacao
	 * @param [out] novoJob    //Retorna o job aqui criado
	*/
Job* CriaJob(char* id) {
	Job* novoJob = (Job*)malloc(sizeof(Job));
	if (novoJob == NULL) return NULL; // Se não há memória

	novoJob->id = id;
	novoJob->listaOperacoes = NULL;
	novoJob->next = NULL;

	return novoJob;

}


/**
	 * Insere um job
	 * @param [in] jobsHeader
	 * @param [in] novoJob
	 * @param [out] jobsHeader    //Retorna o header job
	*/
Job* InsereJob(Job* jobsHeader, Job* novoJob) {
	if (jobsHeader == NULL) {
		jobsHeader = novoJob;
	}
	else {
		novoJob->next = jobsHeader;
		jobsHeader = novoJob;
	}

	return jobsHeader;
}


/**
*Mostra a lista de jobs e operações e máquinas
* @param[in] jobsHeader
*/
void MostraListaJobs(Job * jobsHeader) {
	Job* auxJobs = jobsHeader;
	while (auxJobs != NULL) {
		printf("-----------------------------------------\n");
		printf("ID Job: %s\n", auxJobs->id);
		MostraListaOperacoes(jobsHeader->listaOperacoes);
		auxJobs = auxJobs->next;
	}
}





#pragma endregion 

#pragma region Maquinas
/*
* @brief Criacao de uma nova maquina
* @param[in]    num			número da maquina a criar
* @param[in]    unitempo	unidades de tempo da maquina
* @param[out]	newmaquina	Apontador da Nova maquina
*/
Maquina* criaMaquina(int num, int unitempo) {
	Maquina* newmaquina = (Maquina*)malloc(sizeof(Maquina));
	if (newmaquina == NULL) return NULL;
	newmaquina->num = num;
	newmaquina->unitempo = unitempo;
	newmaquina->next = NULL;
	return newmaquina;
}

/*
* @brief Insercao de uma nova maquina
* @param[in]  h				inico da lista de maquinas
* @param[in]  novamaquina	nova maquina a inserir maquina
* @param[out] h				apontador para novo inicio da lista de maquinas
*/
Maquina* insereMaquina(Maquina* h, Maquina* novamaquina) {
	if (h == NULL) h = novamaquina;
	else {
		novamaquina->next = h; //a primeira maquina passa para o next
		h = novamaquina;
	}
	return h;
}


/*
* @brief Procurar uma maquina
* @param[in]  h				inico da lista de maquinas
* @param[in]  cod			codigo da operacao onde a maquina esta inserida
* @param[in]  num			numero da maquina a procurar
* @param[out] NULL,aux2		NULL se nao encontrarmos, aux2(apontador para maquina que queriamos encontrar)
*/
Maquina* procuraMaquina(Operacao* h, int cod, int num) {
	Operacao* aux1;
	Maquina* aux2;
	if (h == NULL) return NULL; //lista vazia
	else {
		aux1 = procuraOperacao(h, cod);
		if (aux1 == NULL) return NULL;
		else {
			aux2 = aux1->listamaquinas;
			if (aux2 == NULL) return NULL; //lista maquinas vazia
			else {
				while (aux2) {
					if (aux2->num == num) return aux2;
					aux2 = aux2->next;
				}
			}
		}
	}

	return NULL;
}

/**
	 * Alterar operações
	 * @param [in] operacoesHeader
	 * @param [in] id
	 * @param [in] tempoAMudar
	 * @param [in] idMaquina
	 * @param [out] operacaoHeader    //Retorna o header daa lista de operações alterada
	*/
Operacao* AlterarOperacoes(Operacao* operacoesHeader, int idOperacao, int idMaquina, int tempoAMudar) {
	if (operacoesHeader == NULL) return NULL; //Lista vazia
	Operacao* auxOperacoes = operacoesHeader;

	while (auxOperacoes != NULL) {
		if (auxOperacoes->cod == idOperacao) {
			Maquina* auxMaquinas = auxOperacoes->listamaquinas;
			while (auxMaquinas != NULL) {
				if (auxMaquinas->num == idMaquina)
					auxMaquinas->unitempo = tempoAMudar;
				auxMaquinas = auxMaquinas->next;
			}
		}
		auxOperacoes = auxOperacoes->next;
	}

	return operacoesHeader;
}

/*
* @brief Alteracao do conteudo de uma maquina
* @param[in] h				inico da lista de maquinas
* @param[in] cod			codigo da operacao onde a maquina esta inserida
* @param[in] num			numero da maquina a procurar
* @param[in] novonum		novo numero da maquina
* @param[in] novounitempo	novoa unidade de tempo
* @param[out]				void
*/
void alteraMaquina(Maquina* h, int num, int cod, int novonum, int novounitempo) {
	Maquina* aux = procuraMaquina(h, cod, num);
	aux->num = novonum;
	aux->unitempo = novounitempo;
}


/**
* Mostra a lista de maquinas
* @param [in] operacoesHeader
*/
void MostraListaMaquinas(Maquina* maquinasHeader) {
	Maquina* auxMaquinas = maquinasHeader;
	while (auxMaquinas != NULL) {
		printf("---------------------\n");
		printf("ID: %d\n Tempo: %d\n", auxMaquinas->num , auxMaquinas->unitempo);
		auxMaquinas = auxMaquinas->next;
	}
}
#pragma endregion 

#pragma region Operacoes 
/**
*@brief Cria nova Operacao.
*@param [in] cod         Código da Operacao
*@param[out] newoperacao Nova Operacao
*/
Operacao* criaOperacao(int cod) {
	Operacao* newoperacao = (Operacao*)malloc(sizeof(Operacao));
	if (newoperacao == NULL) return NULL;//pode não haver memória
	newoperacao->cod = cod;
	newoperacao->listamaquinas = NULL;
	newoperacao->next = NULL;
	return newoperacao;
}

/**
* @brief Insere Operacao ordenado pelo código
* @param [in] h		       Inicio da Lista
* @param [in] novaoperacao Nova Operacao a inserir
* @param[out] h			   Inicio da Lista
*/
Operacao* insereOperacaoOrdenada(Operacao* h, Operacao* novaoperacao) {
	if (procuraOperacao(h, novaoperacao->cod) != NULL) return h; 
	if (h == NULL) {
		h = novaoperacao; //insere diretamente se a lista estiver vazia
	}

	else {
		Operacao* aux = h;
		Operacao* auxant = NULL;
		while (aux && aux->cod < novaoperacao->cod) {
			auxant = aux;
			aux = aux->next;
		}
		if (auxant == NULL) { //insere se houver só um elemento na lista
			novaoperacao->next = h;
			h = novaoperacao;
		}

		else { // insere em qualquer lugar na lista segundo a condicao
			auxant->next = novaoperacao;
			novaoperacao->next = aux;
		}
	}
	return h;
}

/**
* @brief Verifica se Operacao existe. Se existir devolve endereço da Operacao!
* @param [in] h		    Inicio da Lista
* @param [in] cod	    código da Operacao a procurar
* @param[out] aux,NULL	Apontador para Operacao encontrada
*/
Operacao* procuraOperacao(Operacao* h, int cod) {
	Operacao* aux = h;
	if (aux == NULL) return h;
	else {
		while (aux) {
			if (aux->cod == cod) return aux;   //Procura operacao através do codigo na estrutura

			aux = aux->next;    //avança para a proxima estrutura se ainda nao tiver encontrado a que procura
		}
	}
	return NULL;
}

/*Operacao* removeOperacao(Operacao* h, int cod) {
	if (h == NULL) return NULL;

	else if (h->cod == cod) {
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}

	else {
		Operacao* aux = h;
		Operacao* auxant = NULL;

		while (aux && aux->cod != cod) {
			auxant = aux;
			aux = aux->next;
		}

		if(aux != NULL){
			auxant->next = aux->next;
			free(aux);
		}
	}
	return h;
}*/

/*
* @brief Remove Operacao recursivo
* @param[in]  h			inicio da lista de operacoes
* @param[in]  cod       codigo a encontrar para a operacao a remover
* @param[out] h         NULL se a lista for vazia; h com a operacao ja removida
*/
Operacao* removeOperacaoRecursivo(Operacao* h, int cod) {
	Operacao* aux = NULL;
	if (h == NULL) return NULL;

	else if (h->cod == cod) {
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}

	else {
		h->next = removeOperacaoRecursivo(h->next, cod);
	}
	return h;
}

/**
* @brief Determinação da quantidade mínima de unidades de tempo necessárias para completar o job e listagem das respetivas operações
* @param [in] headoperacao	  Inicio da Lista
* @param[out] headminop	      Soma dos minimos de tempo de cada operacao
*/
Operacao* minTempo(Operacao* headoperacao, int* soma) {
	Operacao* headminop = NULL;
	Operacao* aux = headoperacao;
	Maquina* aux2 = headoperacao->listamaquinas;
	Maquina* maqmincopia = (Maquina*)malloc(sizeof(Maquina));
	Operacao* operacaocopia = (Operacao*)malloc(sizeof(Operacao));
	int min = aux->listamaquinas->unitempo;
	maqmincopia = criaMaquina(aux2->num, aux2->unitempo);

	while (aux) {

		while (aux2) {

			if (aux2->unitempo < min) {
				min = aux2->unitempo;
				maqmincopia = criaMaquina(aux2->num, aux2->unitempo);

			}

			aux2 = aux2->next;
		}

		*soma = *soma + min;

		operacaocopia = criaOperacao(aux->cod);
		operacaocopia->listamaquinas = insereMaquina(operacaocopia->listamaquinas, maqmincopia);
		headminop = insereOperacaoOrdenada(headminop, operacaocopia);

		aux = aux->next;

		if (aux != NULL) {
			aux2 = aux->listamaquinas;
			min = aux->listamaquinas->unitempo;
		}
	}

	return headminop;
}

/**
* @brief Determinação da quantidade maxima de unidades de tempo necessárias para completar o job e listagem das respetivas operações
* @param [in] headoperacao	 Inicio da Lista
* @param[out] headmaxop      Soma dos minimos de tempo de cada operacao
*/
Operacao* maxTempo(Operacao* headoperacao, int* soma) {
	Operacao* headmaxop = NULL;
	Operacao* aux = headoperacao;
	Maquina* aux2 = headoperacao->listamaquinas;
	Maquina* maqmaxcopia = (Maquina*)malloc(sizeof(Maquina));
	Operacao* operacaocopia = (Operacao*)malloc(sizeof(Operacao));
	int max = aux->listamaquinas->unitempo;
	maqmaxcopia = criaMaquina(aux2->num, aux2->unitempo);

	while (aux) {

		while (aux2) {

			if (aux2->unitempo > max) {
				max = aux2->unitempo;
				maqmaxcopia = criaMaquina(aux2->num, aux2->unitempo);

			}

			aux2 = aux2->next;
		}

		*soma = *soma + max;

		operacaocopia = criaOperacao(aux->cod);
		operacaocopia->listamaquinas = insereMaquina(operacaocopia->listamaquinas, maqmaxcopia);
		headmaxop = insereOperacaoOrdenada(headmaxop, operacaocopia);

		aux = aux->next;

		if (aux != NULL) {
			aux2 = aux->listamaquinas;
			max = aux->listamaquinas->unitempo;
		}
	}

	return headmaxop;
}

/**
* @brief  Determinação da quantidade média de unidades de tempo necessárias para completar uma operação,considerando todas as alternativas possíveis
* @param [in] headoperacao		      Inicio da Lista
* @param [in] cod	                  código da Operacao
* @param[out] somatempo/somamaquina	  Media
*/
float media(Operacao* headoperacao, int cod) {

	Maquina* aux = procuraOperacao(headoperacao, cod)->listamaquinas;
	float somamaquina = 0, somatempo = 0;

	while (aux != NULL) {

		somamaquina++;
		somatempo += aux->unitempo;
		aux = aux->next;

	}

	return(somatempo / somamaquina);
}

/**
* @brief  Conta quantas operacoes existem
* @param [in] headoperacao    Inicio da Lista
* @param[out] count           Numero de operacoes
*/
int contaOperacoes(Operacao* h) {
	Operacao* aux = h;
	int count = 0;

	if (aux == NULL) return NULL;

	while (aux) {

		count++;
		aux = aux->next;

	}

	return count;

}

/**
	 * Mostra a lista de operações e máquinas
	 * @param [in] operacoesHeader
	*/
void MostraListaOperacoes(Operacao* operacoesHeader) {
	Operacao* auxOperacoes = operacoesHeader;
	while (auxOperacoes != NULL) {
		printf("---------------------\n");
		printf("ID: %d\n", auxOperacoes->cod);
		MostraListaMaquinas(auxOperacoes->listamaquinas);
		auxOperacoes = auxOperacoes->next;
	}
}
#pragma endregion

#pragma region Ficheiros

/**
* @brief  Ler de um ficheiro de texto
* @param [in] fp              FilePointer
* @param [in] nome            Nome do Ficheiro
* @param[out]                 void
*/
void lerFicheiros(FILE* fp, char nome[100]) {
	char c[100];

	//handler de ficheiro de entrada
	fp = fopen(nome, "r"); // abrir ficheiro em modo leitura

	//se houve algum problema...
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}  


	int l = 1;		//conta linhas lidas
	int linOper = 0;
	while (fscanf(fp, "%[^\n] ", c) != EOF) {	//lê até ao fim da linha
		printf("File:\n%s\n", c);
		if (l == 1)
		{
			int proc, maq, oper;
			int x = sscanf(c, "%dx%dx%d", &proc, &oper, &maq);
			printf("Proc: %d, Oper: %d, Maq: %d\n", proc, oper, maq);
			l++;
			continue;
		}
		if (l == 2) {
			char s[40];
			int numOper;
			int x = sscanf(c, "%s%*c%d", s, &numOper);	//%*c...encontra o char e não guarda!!!
			printf("Proc: %s, Oper: %d\n", s, numOper);
			l++;
			linOper = numOper;
			continue;
		}
		if (linOper > 0) {
			int m, t;
			char* field;
			field = strtok(c, "-");
			while (field != NULL) {
				printf("%s\n", field);
				field = strtok(NULL, "-");
			}
			linOper--;
			continue;
		}
	}
	fclose(fp);

}

/**
* @brief  Escrever num ficheiro de texto
* @param [in] h               headOperacao
* @param [in] fp              FilePointer
* @param [in] nome            Nome do Ficheiro
* @param[out]                 void
*/
void escreverFicheiros(Operacao* h, FILE* fp, char nome[100]) {

	Operacao* aux = h;
	int linha = 1, count = 0;
	char tabela[100] = "8x7x8";

	fp = fopen(nome, "w"); // abrir ficheiro em modo escrita

	//se houve algum problema...
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}

	while (aux) {

		if (linha == 1) {

			fprintf(fp, "%s\n", tabela);
			linha++;
			continue;

		}
		if (linha == 2) {

			count = contaOperacoes(aux);
			fprintf(fp, "1 %d\n", count);
			linha++;
			//aux = aux->next;
			continue;

		}
		if (count > 0) {

			while (aux->listamaquinas) {

				if (aux->listamaquinas->next == NULL) {

					fprintf(fp, "(%d,%d)\n", aux->listamaquinas->num, aux->listamaquinas->unitempo);
					break;
				}
				else {

					fprintf(fp, "(%d,%d)-", aux->listamaquinas->num, aux->listamaquinas->unitempo);
					aux->listamaquinas = aux->listamaquinas->next;

				}


			}

			count--;
			aux = aux->next;
			continue;

		}

	}
	fclose(fp);
}

#pragma endregion

#pragma region Planeamento
void IniciaPlano(Cel p[][T], int codJob, int codOper) {

	for (int l = 0; l < M; l++) //linhas
		for (int col = 0; col < T; col++) { //colunas
			p[l][col].idJob = codJob;
			p[l][col].idOper = codOper;
		}
}

/**
 * @brief Ocupa uma unidade de tempo do Plano.
 *
 * @param p		Plano
 * @param mId	Maquina
 * @param t		Tempo
 * @param codJob	Job
 * @param codOper	Operacao
 */
void OcupaUm(Cel p[][T], int mId, int t, int codJob, int codOper) {
	//testar
	p[mId][t].idJob = codJob;
	p[mId][t].idOper = codOper;
}

/**
 * @brief Ocupa várias unidades de tempo.
 *
 * @param p	- Plano
 * @param mId	- Maquina
 * @param totTempo	- Tempo a ocupar
 * @param c	- Job e Operacao
 */
void OcupaVarios(Cel p[][T], int mId, int totTempo, Cel* c) {

	//Fase 1: Procurar a primeira "casa" livre
	int col = 0;
	while (p[mId][col].idJob != -1)
		col++;

	//Fase 1 - Ocupa a partir da posição livre encontrada
	totTempo += col;	//porquê?
	for (; col < totTempo; col++) {
		p[mId][col].idJob = c->idJob;
		p[mId][col].idOper = c->idOper;
		//p[mId][col] = *c;
	}

	//Fase 2 - Procurar quando a operação anterior

	//Fase 3 - Verficar se após posição livre existe tempo suficiente...
}

void Ocupa(Cel p[][T], int mId, int totTempo, int codJ, int codO) {
	Cel c = { .idJob = codJ, .idOper = codO };
	OcupaVarios(p, mId, totTempo, &c);
}


bool SavePlan(char* fileName, Cel p[][T]);

Cel** GetPlan(char* fileName);

/**
 * @brief Carrega dados de um ficheiro CSV.
 *
 * @param fileName
 * @return
 */
Job* CarregarDadosFicheiro(char* fileName) {
	FILE* fp;
	char texto[MAX1];
	int a, b, c, d;

	Job* listaJobs = NULL;

	Job auxJob;
	Operacao auxOper;
	Maquina auxMaq;

	//char d[20];

	fp = fopen(fileName, "r");
	if (fp == NULL) return;

	while (!feof(fp)) {
		//fgets
		//fscanf()
		if (fgets(texto, MAX, fp) != NULL)
		{
			//printf("Texto: %s\n", texto);
			//analisar o texto do ficheiro
			//3333;sddfsds;224;3434
			//sscanf(texto, "%d;%[^;];%d;%d", &a, d, &b, &c);
			sscanf(texto, "%d;%d;%d;%d", &auxJob.id, &auxOper.cod, &auxMaq.num, &auxMaq.unitempo);
			printf("LIDO: %d - %d - %d - %d \n", auxJob.id, auxOper.cod, auxMaq.num, auxMaq.unitempo);
			/*
			if(ProcuraJob(listaJobs,auxJob.codJob)==NULL)
				listaJobs = InsereJob(listaJobs, auxJob);
			if(ProcuraOperacaoJob(listaJobs, auxOper.cod)==NULL)
				listaJobs = InsereOperacaoJob(listaJobs, auxJob.codJob, auxOper);
			listaJobs = InsereMaquinaOperacaoJob(listaJobs, auxJob.codJob, auxOper.cod, auxMaq);
			*/
		}
	}
	fclose(fp);
	return listaJobs;
}

#pragma endregion

#pragma endregion