#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#pragma region  structs

//Estrutura para a lista do ficheiro sets.tsv
typedef  struct _sets
{
    char set_num[20];
    char name[100];
    int year;
    char theme[100];
    bool possible;
    struct _sets*next;
    struct _sets*previous;
}Sets;

//Estrutura para a lista do ficheiro parts_sets.tsv
typedef struct _parts
{
    char part_num[100];
    char name[100];
    char classe[100];
    int stock;
    struct _parts*next;
    struct _parts* previous;
}Parts;

//Estrutura para a lista do ficheiro parts_sets.tsv
typedef struct _parts_sets
{
    char set_num[100];
    int quantity;
    char part_num[100];
    int stock;
    struct _parts_sets*next;
    struct _parts_sets*previous;
}PartsSets;

//Estrutura criada para assistir na necessidade de guardar alguma informação necessária de uma certa lista
typedef struct
{
    char str[100];
}Saver;

#pragma endregion

#pragma region  inserção à cabeça em listas
PartsSets* head_insert_parts_sets(PartsSets* lst, PartsSets reg)
{
    PartsSets* new= (PartsSets*)malloc(sizeof(PartsSets));
    strncpy(new->set_num,reg.set_num,100);
    new->quantity=reg.quantity;
    strncpy(new->part_num,reg.part_num,100);

    new->next=lst;

    if (new->next)
    {
        new->next->previous=new;
    }
    new->previous=NULL;
    return new;
}

Parts* head_insert_parts(Parts* lst, Parts reg)
{
    Parts *new= (Parts*)malloc(sizeof(Parts));
    strncpy(new->part_num, reg.part_num, 100);
    strncpy(new->name,reg.name, 100);
    strncpy(new->classe,reg.classe, 100);
    new->stock=reg.stock;

    new->next=lst;
    
    if (new->next)
    {
        new->next->previous=new;
    }
    new->previous=NULL;

    return new;
}

Sets* head_insert_sets(Sets* lst, Sets reg)
{
    Sets *new= (Sets*)malloc(sizeof(Sets));
    strncpy(new->set_num,reg.set_num,20);
    strncpy(new->name,reg.name, 100);
    new->year=reg.year;
    new->possible=true;
    strncpy(new->theme, reg.theme, 100);
    
    new->next=new->previous=NULL;

    //Inserção ordenada pelo ano do Conjunto
    if (!lst || lst->year > reg.year)
    {
        new->next=lst;
        lst=new;
        if (lst->next)
        {
            lst->next->previous=lst;
        }
    }
    else
    {
        Sets* aux= lst;
        for (;aux->next && aux->next->year < reg.year; aux= aux->next)
        {
        }
        new->next=aux->next;
        new->previous=aux;
        aux->next=new;
        if (new->next)
        {
            new->next->previous=new;
        }
    }
    
    return lst;
}

#pragma endregion

#pragma region  leitura dos ficheiros
PartsSets* read_parts_sets(PartsSets* lst)
{
    FILE* partsSets=fopen("parts_sets.tsv", "r");
    int i=0;
    char str[200], fLine[100];
    PartsSets v;

    if (partsSets==NULL)
    {
        perror("Unable to open the file requested!");
    }
    else
    {
        while (!feof(partsSets))
        {
            //Caso seja a primeira linha não faz scan das variaveis
            if (i==0)
            {
                fgets(fLine, sizeof(fLine), partsSets);
            }
            //Em qualquer outra linha lê as variaveis existentes
            else
            {
                fflush(stdin);
                fgets(str, sizeof(str), partsSets);
                sscanf(str, "%[^\t]\t%d\t%s", v.set_num, &v.quantity, v.part_num);
                lst=head_insert_parts_sets(lst, v);
            }
            i++;
        }
    }
    return lst;
}

Parts *read_Parts(Parts *lst)
{
    FILE *parts = fopen("parts.tsv", "r");
    int i = 0;
    char str[200], fLine[100];
    Parts v;

    if (parts == NULL)
    {
        perror("Não foi possível abrir o ficheiro solicitado!");
    }
    else
    {
        while (!feof(parts))
        {
            //Caso seja a primeira linha não faz scan das variaveis
            if (i == 0)
            {
                fgets(fLine, sizeof(fLine), parts);
            }
            //Em qualquer outra linha lê as variaveis existentes    
            else
            {
                fflush(stdin);
                fgets(str, sizeof(str), parts);
                sscanf(str, "%s\t%[^\t]%s\t%d", v.part_num, v.name, v.classe, &v.stock);
                lst = head_insert_parts(lst, v);
            }
            i++;
        }
    }
    return lst;
}

Sets* read_Sets(Sets* lst)
{
    FILE* sets=fopen("sets.tsv", "r");
    int i=0;
    char str[200], fLine[100];
    Sets v;

    if (sets==NULL)
    {
        perror("Unable to open the file requested!");
    }
    else
    {
        while (!feof(sets))
        {   
            //Caso seja a primeira linha não faz scan das variaveis
            if (i==0)
            {
                fgets(fLine, sizeof(fLine), sets);
            }
            //Em qualquer outra linha lê as variaveis existentes
            else
            {
                fflush(stdin);
                fgets(str, sizeof(str), sets);
                sscanf(str, "%s\t%[^\t]\t%d\t%s", v.set_num, v.name, &v.year, v.theme);
                lst = head_insert_sets(lst, v);
            }        
            i++;
        }
    }
    return lst;
}

#pragma endregion

#pragma region procedimentos para listar os elementos da lista

void visit_list_parts_sets(PartsSets * lst)
{
    PartsSets* aux=lst;
    printf("||--------------||--------- ||----------------------||\n");
    printf("||    Set_num   || quantity ||      Part_num        ||\n");
    printf("||--------------||--------- ||----------------------||\n");
    while (aux)
    {
        printf("||%13s || %5d    || %20s ||\n", aux->set_num, aux->quantity, aux->part_num);
        printf("||--------------||----------||----------------------||\n");
        aux=aux->next;
    }
}
void visit_list_parts(Parts * lst)
{
    Parts*aux=lst;

    printf("||---------------||---------------------------------------------------------------------------------------------------||----------------------||------||\n");
    printf("||     Part_num  ||                                                      Name                                         ||          Class       || stock||\n");
    printf("||---------------||---------------------------------------------------------------------------------------------------||----------------------||------||\n");
    while (aux!=NULL)
    {
        printf("||  %10s   ||  %96s || %20s ||%5d ||\n", aux->part_num, aux->name, aux->classe, aux->stock);
        printf("||---------------||---------------------------------------------------------------------------------------------------||----------------------||------||\n");
        aux=aux->next;
    }
}

void visit_list_sets(Sets * lst)
{
    Sets*aux=lst;

    printf("||----------------||------------------------------------------------------------------------------------||---------||-----------------------------------||\n");
    printf("||     Set_num    ||                                     Name                                           ||   year  ||                Theme              ||\n");
    printf("||----------------||------------------------------------------------------------------------------------||---------||-----------------------------------||\n");
    while (aux!=NULL)
    {
        printf("||%13s   || %80s   || %5d   || %30s    ||\n", aux->set_num, aux->name, aux->year, aux->theme);
        printf("||----------------||------------------------------------------------------------------------------------||---------||-----------------------------------||\n");
        aux=aux->next;
    }
}

#pragma endregion

#pragma region procedimentos e funções

//1º: Procedimento para determinar os conjuntos de cada tema
void themeSets(Sets*lst)
{
    Sets*NameAux=lst;
    Sets*aux2=lst;
    char input[100];
    fflush(stdin);
    printf("Name of the theme you want to search for: ");
    scanf("%[^\n]s", input);

    printf("Sets for the theme %s\n", input);
    printf("\t||---------------||----------------------------------------------------------------------------------||----------||\n");
    printf("\t||    Set_num    ||                                    Name                                          ||   Year   ||\n");
    printf("\t||---------------||----------------------------------------------------------------------------------||----------||\n");
    //percorrer a lista Sets
    while (NameAux)
    {
        //verificar se o tema para onde o apontador aponta é igual ao input do utilizador
        if (strcasecmp(NameAux->theme,input)==0)
        {
            printf("\t||%12s   || %80s ||   %d   ||\n", NameAux->set_num, NameAux->name, NameAux->year);
            printf("\t||---------------||----------------------------------------------------------------------------------||----------||\n");
        }
        NameAux=NameAux->next;        
    }
}

//2º-Procedimento para determinar as peças de determinado tipo em determinado conjuntos
void searchPieceSet(Parts* lstParts, PartsSets* lstPartsSets)
{
    char inputPiece[100];
    char inputSet[100];
    
    fflush(stdin);
    printf("Type of piece you want to search for: ");
    scanf("%[^\n]s",inputPiece);
    fflush(stdin);
    printf("The set where you want to search for the piece in: ");
    scanf("%[^\n]s",inputSet);

    Parts* auxPieces=lstParts;
    PartsSets* auxSets=lstPartsSets;
    Saver pieces[19000];
    int savedPieces=0;
    int found=0;

    //percorrer a lista das Parts
    while (auxPieces)
    {
        //e guardar todas as peças que sejam da mesma classe do input do utilizador
        if (strcasecmp(inputPiece,auxPieces->classe)==0)
        {
            strcpy(pieces[savedPieces].str, auxPieces->part_num);
            savedPieces++;
        }
        auxPieces=auxPieces->next;
    }
    auxPieces=lstParts;
    printf("Pieces of the type %s in the set %s:\n", inputPiece, inputSet);
    //percorrer a lista PartsSets
    while (auxSets)
    {
        //verificar se o set é igual ao input do utilizador
        if (strcasecmp(inputSet, auxSets->set_num)==0)
        {
            for (int i = 0; i < savedPieces; i++)
            {
                //verificar se as peças desse set são iguais às guardadas anteriormente
                if (strcasecmp(auxSets->part_num,pieces[i].str)==0)
                {
                    printf("\t%s\n", auxSets->part_num);
                    found++;
                }   
            }
        }
        auxSets=auxSets->next;
    }
    if (found==0)
    {
        printf("No pieces of that type were found in the refered set\n");
    }
}

//3º: Procedimento para determinar as peças necessárias para acabar um determinado conjunto
void necessaryPieces(PartsSets*lstPartsSets, Parts*lstParts)
{
    PartsSets*auxPartsSets=lstPartsSets;
    Parts*auxParts=lstParts;
    char input[100];
    char set_num[100];
    fflush(stdin);
    printf("Name of the set you want to search for: ");
    scanf("%[^\n]s",input);
    
    printf("|------------|-------------------------------------------------------------------------------------------|--------------------|---------------|-------|\n");
    printf("|   Piece    |                                 Name                                                      |        Class       |Needed quantity|Stock  |\n");
    printf("|------------|-------------------------------------------------------------------------------------------|--------------------|---------------|-------|\n");
    //percorrer a lista Parts_Sets
    while (auxPartsSets)
    {
        //Verificar se existe um set igual ao dado por input pelo utilizador
        if (strcasecmp(auxPartsSets->set_num,input)==0)
        {
            auxParts=lstParts;
            //se existir vai listar essa peça, percorrer a lista Parts
            //e procurar a peça e listar o resto das suas informações
            printf("|%12s", auxPartsSets->part_num);
            while (auxParts)
            {
                if (strcasecmp(auxPartsSets->part_num,auxParts->part_num)==0)
                {
                    printf("|%90s ", auxParts->name);
                    printf("|%20s", auxParts->classe);
                    printf("|%15d", auxPartsSets->quantity);
                    printf("|%7d|\n", auxParts->stock);
                    printf("|------------|-------------------------------------------------------------------------------------------|--------------------|---------------|-------|\n");
                }
                auxParts=auxParts->next;
            }  
        }
        auxPartsSets=auxPartsSets->next;
    }
}

//4º: Função para devolver o nº de peças em stock
int piecesInStock(Parts* lst)
{
    Parts* aux=lst;
    int sum=0;

    //Percorrer a lista Parts e somar o stock de todas as peças
    while (aux)
    {
        sum+=aux->stock;
        aux=aux->next;
    }
    return sum;
}

//5ª: Função para devolver o numero de peças num determinado num determinado conjunto
int piecesInSet(PartsSets* lst)
{
    PartsSets* aux=lst;
    int sum=0, i=0;
    char inputSet[100];

    fflush(stdin);
    printf("Set you would like to analyze: ");
    scanf("%[^\n]s", inputSet);
    
    //Percorrer a lista Parts_Sets e verificar se existe algum set igual ao input do utilizador
    while (aux)
    {
        //Se existir somar a sua quantidade à variável sum
        if (strcasecmp(aux->set_num,inputSet)==0)
        {
            sum+=aux->quantity;
        }
        aux=aux->next;
    }
    if (sum>0)
    {
        return sum;
    }
    else
    {
        return 0;
    }
}

//6º: Procedimento para determinar a peça mais usada em conjuntos diferentes
void most_used(PartsSets* lstPartSets, Parts* lstParts)
{
    Parts *auxParts=lstParts;
    PartsSets *auxPartsSets=lstPartSets;
    Parts* most_used=lstParts;
    int counter=0, biggest;

    while (auxParts)
    {
        counter=0;
        auxPartsSets=lstPartSets;
        while (auxPartsSets)
        {
            if (strcasecmp(auxParts->part_num, auxPartsSets->part_num)==0)
            {
                counter++;
            }
            auxPartsSets=auxPartsSets->next;
        }
        if (counter>biggest)
        {
            biggest=counter;
            most_used=auxParts;
        }
        auxParts=auxParts->next;
    }
    
    auxParts=lstParts;
    printf("Most used piece %s\n", most_used->part_num);
    
}

//7º: Procedimento para determinar os conjuntos que se podem construir com o stock existente
void BuildSet(PartsSets* lstPartsSets, Parts* lstParts, Sets* lstSets)
{
    PartsSets* auxQtd= lstPartsSets;
    Parts* auxStck=lstParts;
    Sets* auxSets=lstSets;
    Saver read[12000];
    int saved=0, in=0;
    char input[100];
    
    //Percorrer a lista Parts_Sets
    while(auxQtd)
    {
        auxStck=lstParts;
        //Percorrer a lista Parts
        while(auxStck)
        {
            //Verificar se existe alguma peça na lista Parts igual á peça apontada da lista Parts_Sets
            if (strcasecmp(auxQtd->part_num,auxStck->part_num)==0)
            {
                //Se o stock dessa peça for menor à quantidade necessária para construir o set
                if (auxStck->stock<auxQtd->quantity)
                {
                    auxSets=lstSets;
                    //percorrer os sets diferentes da lista Sets
                    while(auxSets)
                    {
                        //Se encontrar um set igual à da peça que não tem stock suficiente
                        if (strcasecmp(auxSets->set_num,auxQtd->set_num)==0)
                        {
                            //Dizer que é impossivel construir set tornando variavel bool da posição do array falsa
                            auxSets->possible=false;
                        }
                        auxSets=auxSets->next;
                    }
                }
            }
            auxStck=auxStck->next;
        }
        auxQtd=auxQtd->next;
    }   
    auxSets=lstSets;
    //Percorrer o array de sets diferentes e listar os que são possiveis construir
    while(auxSets)
    {
        if(auxSets->possible)
        {
            in++;
            printf("%s\n", auxSets->set_num);
        }
        auxSets=auxSets->next;
    }
    printf("Number of possible sets:%d\n", in);
}

#pragma endregion

#pragma region funções extra

//Funçao para mudar o stock de uma determinada peça
Parts* changeStock(Parts*lst)
{
    Parts* aux=lst;
    char input[100];
    int opt, qtd;

    fflush(stdin);
    printf("Piece you want to change the stock of: ");
    scanf("%[^\n]s", input);

    fflush(stdin);
    //Perguntar ao utilizador se pretende remover ou adicionar ao stock
    printf("Do you want to add or remove from the set?\n1-Remove\n2-Add\nChoice: ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        aux=lst;
        printf("Quantity to remove: ");
        scanf("%d", &qtd);
        while (aux)
        {
            if (strcasecmp(aux->part_num,input)==0)
            {
                if (aux->stock>=qtd)
                {
                    aux->stock=aux->stock-qtd;
                }
                printf("Invalid quantity!\n");
            }
            aux=aux->next;
        }
        break;
    case 2:
        aux=lst;
        printf("Quantity to add: ");
        scanf("%d", &qtd);
        while (aux)
        {
            if (strcasecmp(aux->part_num,input)==0)
            {
                aux->stock=aux->stock+qtd;
            }
            aux=aux->next;
        }
        break;
    default:
        break;
    }
    return lst;
}

//Funçao para mudar o stock das peças de acordo com o conjunto escolhido
Parts* changeStockBySet(Parts* lstParts, PartsSets* lstPartsSets)
{
    PartsSets* auxPartsSets= lstPartsSets;
    Parts* auxParts=lstParts;
    char input[100];

    fflush(stdin);
    printf("Identify the set of pieces you want to add: ");
    scanf("%[^\n]s", input);

    while (auxPartsSets)
    {
        if (strcasecmp(auxPartsSets->set_num, input)==0)
        {
            auxParts=lstParts;
            while (auxParts)
            {
                if (strcasecmp(auxParts->part_num,auxPartsSets->part_num)==0)
                {
                    auxParts->stock=auxParts->stock+auxPartsSets->quantity;
                }
                auxParts=auxParts->next;
            }
            
        }
        auxPartsSets=auxPartsSets->next;
    }
    return lstParts;
}

//Função para remover todas as peças de uma determinada classe
Parts* removeParts(Parts * lst)
{
    char input[100];
    Parts* aux=lst;

    fflush(stdin);
    printf("What class of parts do you want to remove?: ");
    scanf("%[^\n]s",input);

    for (; aux; aux=aux->next)
    {
        if (strcasecmp(aux->classe,input)==0)
        {
            if(aux->next)
                aux->next->previous = aux->previous;
            if(aux->previous)
                aux->previous->next = aux->next;
            else
                lst = aux->next;
            free (aux ); 
        }
    }
    return lst;
}

//Função para remover todos os sets de um determinado tema
Sets* removeSets(Sets* lst)
{
    char input[100];
    Sets* aux=lst;

    fflush(stdin);
    printf("What theme of sets do you want to remove?: ");
    scanf("%[^\n]s",input);

    for (; aux; aux=aux->next)
    {
        if (strcasecmp(aux->theme,input)==0)
        {
            if(aux->next)
                aux->next->previous = aux->previous;
            if(aux->previous)
                aux->previous->next = aux->next;
            else
                lst = aux->next;
            free (aux ); 
        }
    }
    return lst;
}

#pragma endregion

#pragma region Menu e informações
void INFO()
{
    printf("====================================MENU====================================\n");
    printf("1-To see the sets of a certain theme;\n");
    printf("2-To see the pieces of a certain type in a determined set;\n");
    printf("3-To see the necessary pieces to finish a determined set;\n");
    printf("4-To see the number of pieces in stock;\n");
    printf("5-To see the number of pieces in a certain set;\n");
    printf("6-To see the most used piece;\n");
    printf("7-To see the sets you can build with the existing stock;\n");
    printf("8-To chanhe the stock of a certain piece;\n");
    printf("9-To change the stock of certain pieces based on the identifier of a set;\n");
    printf("10-To remove the pieces of a certain class;\n");
    printf("11-To remove all the sets of a certain theme;\n");
    printf("12-To visit a list of your choice;\n");
    printf("0-Exit.\n");
}

void INFO2()
{
    printf("=======VISIT LISTS MENU=======\n");
    printf("1-To see sets list;\n");
    printf("2-To see parts list;\n");
    printf("3-To see Parts Sets list;\n");
    printf("0-Exit\n");
}

void MENU()
{
    int choice;
    Sets* setLst=NULL;
    Parts* partsLst=NULL;
    PartsSets* partsSetsLst=NULL;

    partsLst=read_Parts(partsLst);
    setLst=read_Sets(setLst);
    partsSetsLst=read_parts_sets(partsSetsLst);

    do
    {
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            themeSets(setLst);
            fflush(stdin);
            break;
        case 2:
            searchPieceSet(partsLst, partsSetsLst);
            fflush(stdin);
            break;
        case 3:
            necessaryPieces(partsSetsLst, partsLst);
            fflush(stdin);
            break;
        case 4:
            printf("Pieces in stock: %d\n", piecesInStock(partsLst));
            break;
        case 5:
            printf("Pieces in the selected set: %d\n", piecesInSet(partsSetsLst));
            break;
        case 6:
            most_used(partsSetsLst, partsLst);
            break;
        case 7:
            BuildSet(partsSetsLst, partsLst, setLst);
            break;
        case 8:
            partsLst=changeStock(partsLst);
            fflush(stdin);
            break;
        case 9:
            partsLst=changeStockBySet(partsLst, partsSetsLst);
            fflush(stdin);
            break;
        case 10:
            partsLst=removeParts(partsLst);
            fflush(stdin);
            break;
        case 11:
            setLst=removeSets(setLst);
            fflush(stdin);
            break;
        case 12:
            INFO2();
            printf("Choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                visit_list_sets(setLst);
                break;
            case 2:
                visit_list_parts(partsLst);
                break;
            case 3:
                visit_list_parts_sets(partsSetsLst);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    } while (choice!=0);   
}

#pragma endregion

int main(int argc, char const *argv[])
{
    INFO();
    MENU();

    return 0;
}