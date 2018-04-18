#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	double value;
	int info;
} INDEXED_VALUE;

int cmp_indexed_val_increasing_order(const void * a, const void * b)
{
	return ((INDEXED_VALUE *) a)->value < ((INDEXED_VALUE *)b)->value;
}

typedef struct{
	int num_data;
	int num_team;
	int num_cord;
	int max_k;
	int count;
	double ** coord;
	INDEXED_VALUE * point;
	int *teamscore;
	int *team;
	double (*metric)(double ** c,double * point,int ncol,int row);
} KNN;


KNN * alloc_knn(int n_data,int num_coordin,int numb_team,int maxk, double (*metric)(double **,double *,int,int))
{
	KNN *knn=malloc(sizeof(KNN));
	if(KNN == NULL) return NULL;
	if(knn == NULL) return free_knn(knn);
	knn->coord=calloc(num_coordin,sizeof(double *));
	knn->point=calloc(n_data,sizeof(INDEXED_VALUE));
	knn->team=calloc(n_data,sizeof(int));
    knn->teamscore=calloc(numb_team,sizeof(int));
	if(!knn->coord || !knn->point || !knn->teamscore || !knn->team) return free_knn(knn);
	for(int i=0;i<num_coordin;i++) if((knn->coord[i]=calloc(n_data,sizeof(double))) == NULL) return free_knn(knn);
	knn->num_data=n_data;
	knn->num_cord=num_coordin;
	knn->num_team=numb_team;
	knn->max_k=maxk;
	knn->count=0;
	knn->metric=metric;
	return knn;
}

void clean_free(void *ptr,int num, int elementsize)
{
	if(ptr == NULL) return NULL;
	memset(ptr,0,num * elementsize);
	free(ptr);
	return NULL;
}

void * free_knn(KNN *knn)
{
	if(knn == NULL) return;
	clean_free(knn->point,knn->num_data,sizeof(INDEXED_VALUE));
	clean_free(knn->teamscore,knn->num_team,sizeof(int));
	clean_free(knn->team,knn->num_data,sizeof(int));
	if(knn->coord == NULL) return;
	for(int i=0;i<knn->num_cord;i++) clean_free(knn->coord[i],knn->num_data,sizeof(double));
	clean_free(knn,1,sizeof(knn));	
	return NULL;
}


//returns 0 upon success
int knn_add_point(KNN *knn,double * data, int team)
{
	if(knn->count >= knn->num_data) return 1;
	if(team >= knn->num_team) return 2;
	if()
	for(int i=0;i<knn->num_coord;i++) knn->coord[i][knn->count]=data[i];
	knn->team[i]=team;
	knn->count++;
	return 0;
}


int knn_predict(KNN *knn,double *pr,int k)
{
	if(knn == NULL || ptr == NULL || k > knn->max_k) {
		fprintf(stderr,"Nuclear Error");
		exit(1);
	}
	for(int i=0;i<knn->num_data;i++){
		knn->point[i].value=knn->metric(knn->coord,pr,knn->num_cord,knn->num_data);
		knn->point[i].info=knn->team[i];
	}
	qsort(knn->point,knn->num_data,sizeof(INDEXED_VALUE),cmp_indexed_val_increasing_order);
	memset(knn->teamscore,0,knn->num_team * sizeof(int));
	for(int i=0;i<k;i++){
		knn->teamscore[knn->point[i].info]++;
	}
	int max=0,maxpos=-1;
	for(int i=0;i<knn->num_team;i++){
		if(knn->teamscore[i] > max){
			max=knn->teamscore[i];
			maxpos=i;
		}
	}
	return maxpos;
}




















