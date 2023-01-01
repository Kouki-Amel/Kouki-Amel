#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct voyage
{
    float prix;
    char Num[10];
    char lieudep[100];
    char lieuarr[100];
    char datedep[11];
    char heureemb[6];;
    int placedisp;
    
}voy;

voy* selection(voy *v)
{
    printf("Reference du Vol: ");
    scanf("%s",v->Num);
    fflush(stdin);
    printf("Lieu de depart: ");
    scanf("%s", v->lieudep);
    fflush(stdin);
    printf("Lieu d'arrive: ");
    scanf("%s", v->lieuarr);
    fflush(stdin);
    printf("Date de depart jj/mm/aaaa: ");
    scanf("%s", v->datedep);
    fflush(stdin);
    printf("Heure d'embarquement --:--: ");
    scanf("%s", v->heureemb);
    fflush(stdin);
    printf("Places disponibles: ");
    scanf("%d", &v->placedisp);
    fflush(stdin);
    printf("Prix: ");
    scanf("%f", &v->prix);
    fflush(stdin);
    return v;
}
int main();
void modif_voy(voy* v)
{
    char ch[10];
    int req = (int)malloc(sizeof(int));
    FILE *f = fopen("voyage.txt","r");
    FILE * fp = fopen("temp.txt","a");
    voy* vtest = (voy*) malloc(sizeof(voy));
    int bool =0;
    while(fread(vtest, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, vtest->Num)))
        {
            bool = 1;
            do{
                printf("Changer:\n\t1.Date de depart\n\t2.Heure d'embarquement\n\t3.Lieu de depart\n\t4.Lieu d'arrive\n\t5.Nbre de place disponible: \n\t6.Prix\n\t7.Annuler\nReq >> ");
                scanf("%d",req);
                switch(*req)
                {
                case 1:
                    printf("Nouvelle date jj/mm/aaaa: ");
                    scanf("%s",vtest->datedep);
                    fflush(stdin); 
                    break;
                case 2:
                    printf("Nouvelle Heure d'embarquement --:--: ");
                    scanf("%s",vtest->heureemb);
                    fflush(stdin); 
                    break;
                case 3:
                    printf("Nouveau Lieu de depart: ");
                    scanf("%s",vtest->lieudep);
                    fflush(stdin);
                    break;
                case 4:
                    printf("Nouveau Lieu d'arrive: ");
                    scanf("%s",vtest->lieuarr);
                    fflush(stdin);
                    break;
                case 5:
                    printf("Nbre de place disponible: ");
                    scanf("%d",vtest->placedisp);
                    fflush(stdin);

                    break;
                case 6:
                    printf("Nouveau prix: ");
                    scanf("%f",vtest->prix);
                    fflush(stdin);
                    break;
                case 7:
                    break;
                default:
                    modif_voy(v);
                }
            }while(*req != 7);
            fwrite(vtest, sizeof(voy),1,fp);
        }
        else{
            fwrite(vtest, sizeof(voy),1,fp);
        }
    }
    fclose(fp);
    fclose(f);
    if(bool)
    {
        FILE * fp = fopen("temp.txt","r");
        FILE *f = fopen("voyage.txt","w");
        fclose(f);
        f = fopen("voyage.txt","a");
        while(fread(vtest, sizeof(voy), 1, fp) == 1)
        {
            fwrite(vtest, sizeof(voy),1,f);
        }
        fclose(f);
        fclose(fp);
    }
    else{
        printf("###ce voyage n'existe pas###\n\n");
    }
}
int add_voy(voy *v)
{
    int req = (int)malloc(sizeof(int));
    FILE *f = fopen("voyage.txt","r");
    voy vtest;
    int bool = 0;
    v = selection(v);
    while(fread(&vtest, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, vtest.Num)))
        {
            bool = 1;
            printf("####Existe déjà####\n");
            printf("Do you want to modify the flight? >> 0.YES / 1.NO >> ");
            scanf("%d",req);
            if(*req == 0){modif_voy(&vtest);}
            else{return main();}
        }
    }
    if(!bool){
        fclose(f);
        f = fopen("voyage.txt","a");
        fwrite(v, sizeof(voy),1,f);
    }
    fclose(f);
    main();
}

void aff_voy(voy* v)
{
    char ch[10];
    FILE *f = fopen("voyage.txt","r");
    if(f == NULL)
    {
        printf("###Error opening file###");
    };
    printf("Reference du vol: ");
    scanf("%s", ch);
    fflush(stdin);
    int bool =0;
    while (fread(v, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, ch)))
        {
            printf(" ----------------------------------------------------------------------\n");
            printf("| Heure d'embarquement: ");
            printf("%s", v->heureemb);
            printf("\t\t\t\t%s\n",v->datedep);
            printf("| Lieu de depart: ");
            printf("%s",v->lieudep);
            printf("\t\t\t\tLieu d'arrive: ");
            printf("%s\n",v->lieuarr);
            printf("| Ref: ");
            printf("%s\n",v->Num);
            printf("| Prix: ");
            printf("%f\t\t\t\t\n",v->prix);
            printf(" ----------------------------------------------------------------------\n");
            bool =1;
        }
    }
    if(!bool)
    {
        printf("###ce voyage n'existe pas###\n\n");
    }
    main();
}

void supp_voy(voy* v)
{
    char ch[10];
    FILE *f = fopen("voyage.txt","r");
    FILE * fp = fopen("temp.txt","a");
    printf("Reference du vol: ");
    scanf("%s", ch);
    fflush(stdin);
    int bool =0;
    while(fread(v, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, ch)))
        {
            bool = 1;
        }
        else{
            fwrite(v, sizeof(voy),1,fp);
        }
    }
    fclose(fp);
    fclose(f);
    if(bool)
    {
        FILE * fp = fopen("temp.txt","r");
        FILE *f = fopen("voyage.txt","w");
        fclose(f);
        f = fopen("voyage.txt","a");
        while(fread(v, sizeof(voy), 1, fp) == 1)
        {
            fwrite(v, sizeof(voy),1,f);
        }
        fclose(f);
        fclose(fp);
    }
    else{
        printf("###ce voyage n'existe pas###\n\n");
    }
    main();
}

void modify_voy(voy* v)
{
    char ch[10];
    int req = (int)malloc(sizeof(int));
    FILE *f = fopen("voyage.txt","r");
    FILE * fp = fopen("temp.txt","a");
    printf("Reference du vol: ");
    scanf("%s", ch);
    fflush(stdin);
    int bool =0;
    while(fread(v, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, ch)))
        {
            bool = 1;
            do{
                printf("Changer:\n\t1.Date de depart\n\t2.Heure d'embarquement\n\t3.Lieu de depart\n\t4.Lieu d'arrive\n\t5.Nbre de place disponible: \n\t6.Prix\n\t7.Annuler\nReq >> ");
                scanf("%d",req);
                switch(*req)
                {
                case 1:
                    printf("Nouvelle date jj/mm/aaaa: ");
                    scanf("%s",v->datedep);
                    fflush(stdin); 
                    break;
                case 2:
                    printf("Nouvelle Heure d'embarquement --:--: ");
                    scanf("%s",v->heureemb);
                    fflush(stdin); 
                    break;
                case 3:
                    printf("Nouveau Lieu de depart: ");
                    scanf("%s",v->lieudep);
                    fflush(stdin);
                    break;
                case 4:
                    printf("Nouveau Lieu d'arrive: ");
                    scanf("%s",v->lieuarr);
                    fflush(stdin);
                    break;
                case 5:
                    printf("Nbre de place disponible: ");
                    scanf("%d",&v->placedisp);
                    fflush(stdin);

                    break;
                case 6:
                    printf("Nouveau prix: ");
                    scanf("%f",&v->prix);
                    fflush(stdin);
                    break;
                case 7:
                    break;
                default:
                    modify_voy(v);
                }
            }while(*req != 7);
            fwrite(v, sizeof(voy),1,fp);
        }
        else{
            fwrite(v, sizeof(voy),1,fp);
        }
    }
    fclose(fp);
    fclose(f);
    if(bool)
    {
        FILE * fp = fopen("temp.txt","r");
        FILE *f = fopen("voyage.txt","w");
        fclose(f);
        f = fopen("voyage.txt","a");
        while(fread(v, sizeof(voy), 1, fp) == 1)
        {
            fwrite(v, sizeof(voy),1,f);
        }
        fclose(f);
        fclose(fp);
    }
    else{
        printf("###ce voyage n'existe pas###\n\n");
    }
    main();
}

void substring(char *orig, char *substr, int index, int length)
{
  if (index >= strlen(orig))
  {
    substr[0] = '\0';
    return ;
  }  
  int i = 0;
  while (i < length && orig[index + i] != '\0')
  {
    substr[i] = orig[index + i];
    i++;
  }

  substr[length] = '\0';
}

int cmpdate(char date1[10], char date2[10]) {
    int res=0;
    // Extract the year, month, and day from both dates
    char year1[5], month1[3], day1[3];
    substring(date1, year1, 6, 4);
    substring(date1, month1, 3, 2);
    substring(date1, day1, 0, 2);

    char year2[5], month2[3], day2[3];
    substring(date2, year2, 6, 4);
    substring(date2, month2, 3, 2);
    substring(date2, day2, 0, 2);

    // Convert the year, month, and day strings to integers
    int y1, m1, d1;
    sscanf(year1, "%d", &y1);
    sscanf(month1, "%d", &m1);
    sscanf(day1, "%d", &d1);

    int y2, m2, d2;
    sscanf(year2, "%d", &y2);
    sscanf(month2, "%d", &m2);
    sscanf(day2, "%d", &d2);

    // Compare the years
    if (y1 > y2){res = 1;}
    if (y1 < y2){res = -1;}
    if(y1 == y2){
        // If the years are the same, compare the months
        if (m1 > m2){res =  1;}
        if (m1 < m2) {res=  -1;}
        if(m1 == m2){
            // If the months are the same, compare the days
            if (d1 > d2){res= 1;}
            if (d1 < d2){res= -1;}
        }
    }
    // If all the values are the same, return 0
    return res;
}

void affiche_voy(voy* v)
{
    char ch[10];
    FILE *f = fopen("voyage.txt","r");
    if(f == NULL)
    {
        printf("###Error opening file###");
        exit(1);
    };
    voy* vtest = (voy*)malloc(sizeof(voy));
    int bool =0;
    while (fread(vtest, sizeof(voy), 1, f) == 1)
    {
        if(!(strcmp(v->Num, vtest->Num)))
        {
            printf(" ----------------------------------------------------------------------\n");
            printf("| Heure d'embarquement: ");
            printf("%s", vtest->heureemb);
            printf("\t\t\t\t%s\n",vtest->datedep);
            printf("| Lieu de depart: ");
            printf("%s",vtest->lieu_depart);
            printf("\t\t\t\tLieu d'arrive: ");
            printf("%s\n",vtest->lieuarr);
            printf("| Ref: ");
            printf("%s\n",vtest->Num);
            printf("| Prix: ");
            printf("%f\t\t\t\t\n",vtest->prix);
            printf(" ----------------------------------------------------------------------\n");
            bool =1;
        }
    }
    if(!bool)
    {
        printf("###ce voyage n'existe pas###\n\n");
    }
}
int existed_voy(voy* v)
{
    char date1[10];
    char date2[10];
    FILE *f = fopen("voyage.txt","r");
    if(f == NULL)
    {
        printf("###Error opening file###");
        exit(1);
    };
    int bool =0;
    printf("Voir Les voyages entre les dates\n\tdate_1 jj/mm/aaaa: ");
    scanf("%s", date1);
    fflush(stdin);
    printf("\tdate_2 jj/mm/aaaa: ");
    scanf("%s", date2);
    fflush(stdin);
    int res0,res1,res2;
    res0 = cmpdate(date1,date2);
    if(!(strcmp(date1,date2))){
        while(fread(v, sizeof(voy), 1, f) == 1)
        {
            res1 = cmpdate(v->datedep,date1);
            if(res1 ==0)
            {
                affiche_voy(v);
                bool = 1;
            }
        }
        if(!bool)
        {
            printf("###Aucun voyage existe###\n\n");
        }
    }
    else{
        while(fread(v, sizeof(voy), 1, f) == 1)
        {
            res1 = cmpdate(v->datedep,date1);
            res2 = cmpdate(v->datedep,date2);
            if((res1 >= 0) &&  (res2 <= 0))
            {
                affiche_voy(v);
                bool = 1;
            }
        }
        if(!bool)
        {
            printf("###Aucun voyage existe###\n\n");
        }
    }
    main();
}

int main()
{
    FILE *f = fopen("voyage.txt","a");
    FILE *fp = fopen("temp.txt", "w");
    voy v = (voy) malloc(sizeof(voy));
    int req;
    printf("Choisir l'operation: \n\t1/Ajouter un voyage\n\t2/Afficher un voyage\n\t3/Supprimer un voyage\n\t4/Modifier un voyage\n\t5/Verifier l'existence d'un voyage\n\t6/EXit\n\n Req >> ");
    scanf("%d",&req);
    switch (req)
    {
    case 1:
        add_voy(v);
        break;
    case 2:
        aff_voy(v);
        break;
    case 3:
        supp_voy(v);
        break;
    case 4:
        modify_voy(v);
        break;
    case 5:
        existed_voy(v);
        break;
    case 6:
        exit(1);
        break;
    default:
        main();
    }
    fclose(f);
    fclose(fp);
    return 0;
}
