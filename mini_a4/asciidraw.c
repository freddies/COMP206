#include <stdio.h>
#include <string.h>
#include <math.h>

//Freddie Liu, 260551011, freddie.liu@mail.mcgill.ca
//remarks
//please use gcc -o asciidraw asciidraw.c -lm to exe due to math.h library
//always initiate the array before use it

int main(){
        //commands declaration
        const char *GRID = "GRID";
        const char *CHAR = "CHAR";
        const char *RECTANGLE = "RECTANGLE";
        const char *LINE = "LINE";
        const char *CIRCLE = "CIRCLE";
        const char *DISPLAY = "DISPLAY";
        const char *END = "END";

        //int & char declaration
        char command[20], ch = '*', input[100],  error[100];
        int xaxis, yaxis, i, j, k, l, vxaxis=0, vyaxis=0, dxaxis, dyaxis;//grid values
        int rx1, rx2, ry1, ry2;//rectangle values
        int lx1, lx2, ly1, ly2;//line values
        int cx1, cy1, crad;//circle values      


        //setting grid
        //determine the input exists and test out if it's either GRID or CHAR
        while (fgets(input, 100, stdin) != NULL){
                if (sscanf(input, "%s %d %d", command, &vxaxis, &vyaxis) && strcmp(command, GRID) == 0){
                        if (vxaxis <= 1000 & vyaxis <= 1000){
                        //GRID declaration & Array Initialization
                        const int xaxis = vxaxis;
                        const int yaxis = vyaxis;
                        char arr[yaxis+1][xaxis+1];//2D Array
                        memset( arr, '\0', (yaxis+1)*(xaxis+1)*sizeof(char) );//Arr Initialization

                        //2nd Input Checkpoint after GRID
                        while (fgets(input, 100, stdin) != NULL){
                                //DISPLAY
                                if(sscanf(input, "%s", command) && strcmp(command, DISPLAY) == 0){                                        for (j = yaxis, k = yaxis; j >= 0, k >= 0; j--, k--){
                                                printf("%d", j%10);
                                                        for (l = 0; l <= xaxis; l++) {                        
                                                                if (arr[k][l] != '\0'){
                                                                        printf("%c", arr[k][l]);
									}
                                                                else{
                                                                        printf(" ");
                                                                }
                                                }
                                                printf("\n");
                                        }
                                        printf(" ");
                                        for (i = 0; i <= xaxis; i++){
                                                printf("%d", i%10);
                                        }
                                        printf("\n");
                                }
                                //RECTANGLE
                                else if (sscanf(input, "%s %d,%d %d,%d", command, &rx1, &ry1, &rx2, &ry2) && strcmp(command, RECTANGLE) == 0){

                                        for (k = yaxis; k >= 0; k--){
                                                for(l = 0; l <= xaxis; l++){
                                                        if ((k == ry2 && l<rx2 && l>=rx1) ||(k == ry1 && l<rx2 && l>=rx1) || (l == rx2 && k<ry1+1 && k>=ry2) || (l == rx1 && k<ry1+1 && k>ry2) || (k==ry2 && k==ry1 && l==rx2 && l==rx1)){
                                                                arr[k][l] = ch;

                                                        }
                                                }
                                        }
                                //      reference check for rect coordinates
                                //      printf("x1=%d,y1=%d,x2=%d,y2=%d\n", rx1, ry1, rx2, ry2);
                                }
                                //LINE
                                else if (sscanf(input, "%s %d,%d %d,%d", command, &lx1, &ly1, &lx2, &ly2) && strcmp(command, LINE) == 0){
                                //      printf("x1=%d,y1=%d,x2=%d,y2=%d\n", lx1, ly1, lx2, ly2);
                                        double slope;
					slope = (double)((double)(ly2-ly1)/(double)(lx2-lx1));
                                        double c;
					c = (double)(ly1 - (double)(slope * lx1));
                                //      printf("%lf %lf\n", slope, c);
                                        for (k = yaxis; k >= 0; k--){
                                                if (lx1 < lx2){
                                                        for(l = 0; l <= xaxis; l++){
								if ( k == ly1 && l == lx1 || k == ly2 && l == lx2 ||lx2>lx1+1 && fabs(ly2-ly1)>1 && ly2>ly1 && k <= ly2 && l <= lx2 && k > (int)(slope*(lx2-1)+c) && l > (int)((ly2-1-c)/slope)|| ly1 == ly2 && l>lx1 && l<lx2 && k == (int)(slope*l+c)|| fabs(ly2-ly1)>1 && ly2>ly1 && l>lx1 && l<lx2 && k <= (int)(slope*l+c) && k > (int)(slope*(l-1)+c) || fabs(ly2-ly1)>1 && ly2>ly1 &&  l>lx1 && l<lx2 && l<=(int)((k-c)/slope) && l > (int)((k-1-c)/slope) || lx2>lx1+1 && fabs(ly2-ly1)>1 && ly1>ly2 && k <= ly1 && l <= lx1 && k > (int)(slope*(lx1+1)+c) && l > (int)((ly1+1-c)/slope) || fabs(ly2-ly1)>1 && ly1>ly2 && l>lx1 && l<lx2 && k <= (int)(slope*l+c) && k > (int)(slope*(l+1)+c) || fabs(ly2-ly1)>1 && ly1>ly2 && l>lx1 && l<lx2 && l<=(int)((k-c)/slope) && l > (int)((k+1-c)/slope) || fabs(ly2-ly1)==1 && ly2>ly1 && l>lx1 && l<lx2-(lx2-lx1)/2 && k == ly1 || fabs(ly2-ly1)==1 && l<lx2 && l>=lx2-(lx2-lx1)/2 && k == ly2 || (lx2-lx1)==1 && ly2>ly1 && k>ly1 && k<ly2-(ly2-ly1)/2 && l == lx1 || (lx2-lx1)==1 && ly2>ly1 && k<ly2 && k>=ly2-(ly2-ly1)/2 && l == lx2 || (lx2-lx1)==1 && ly2<ly1 && k>ly2 && k<ly1-(ly1-ly2)/2 && l == lx2 || (lx2-lx1)==1 && ly2<ly1 && k<ly1 && k>=ly1-(ly1-ly2)/2 && l == lx1){

                                                                        arr[k][l] = ch;
                                                                }
                                                        }
                                                }
						else if (lx1 > lx2){
							for ( l = 0; l <= xaxis; l++){
								if ( k == ly1 && l == lx1 || k == ly2 && l == lx2 ||lx1>lx2+1 && fabs(ly1-ly2)>1 && ly1>ly2 && k <= ly1 && l <= lx1 && k > (int)(slope*(lx1-1)+c) && l > (int)((ly1-1-c)/slope)|| ly1 == ly2 && l>lx2 && l<lx1 && k == (int)(slope*l+c)|| fabs(ly1-ly2)>1 && ly1>ly2 && l>lx2 && l<lx1 && k <= (int)(slope*l+c) && k > (int)(slope*(l-1)+c) || fabs(ly1-ly2)>1 && ly1>ly2 && l>lx2 && l<lx1 && l<=(int)((k-c)/slope) && l > (int)((k-1-c)/slope) || lx1>lx2+1 && fabs(ly1-ly2)>1 && ly2>ly1 && k <= ly2 && l <= lx2 && k > (int)(slope*(lx2+1)+c) && l > (int)((ly2+1-c)/slope) || fabs(ly1-ly2)>1 && ly2>ly1 && l>lx2 && l<lx1 && k <= (int)(slope*l+c) && k > (int)(slope*(l+1)+c) || fabs(ly1-ly2)>1 && ly2>ly1 && l>lx2 && l<lx1 && l<=(int)((k-c)/slope) && l > (int)((k+1-c)/slope) || fabs(ly1-ly2)==1 && l>lx2 && l<lx1-(lx1-lx2)/2 && k == ly2 || fabs(ly1-ly2)==1 && l<lx1 && l>=lx1-(lx1-lx2)/2 && k == ly1 || (lx1-lx2)==1 && ly1>ly2 && k>ly2 && k<ly1-(ly1-ly2)/2 && l == lx2 || (lx1-lx2)==1 && ly1>ly2 && k<ly1 && k>=ly1-(ly1-ly2)/2 && l == lx1 || (lx1-lx2)==1 && ly1<ly2 && k>ly1 && k<ly2-(ly2-ly1)/2 && l == lx1 || (lx1-lx2)==1 && ly1<ly2 && k<ly2 && k>=ly2-(ly2-ly1)/2 && l == lx2){
                                                                        arr[k][l] = ch;
								}
                                                        }
						}
                                                else if (lx1 == lx2 && ly1 <= ly2){
                                                        for (l = 0; l <= xaxis; l++){
                                                                if ( l == lx1 && k <= ly2 && k >= ly1){
                                                                        arr[k][l] = ch;
                                                                }
                                                        }
                                                }
                                                else if (lx1 == lx2 && ly1 > ly2){
                                                        for (l = 0; l <= xaxis; l++){
                                                                if ( l == lx1 && k >= ly2 && k <= ly1){
                                                                        arr[k][l] = ch;
                                                                }
                                                        }
                                                }
                                        }
                                }
				//CIRCLE
                                else if (sscanf(input, "%s %d,%d %d", command, &cx1, &cy1, &crad) && strcmp(command, CIRCLE) == 0){
                                        for (k = yaxis; k >= 0; k--){
                                                for(l = 0; l <= xaxis; l++){
                                                        if ( l == cx1 - crad && k == cy1 || l == cx1 + crad && k == cy1 || l == cx1 && k == cy1 + crad || l == cx1 && k == cy1 - crad || crad*crad-crad < pow(l - cx1, 2) + pow(k - cy1, 2) && crad*crad+crad > pow(l - cx1, 2) + pow(k - cy1, 2)){
                                                                arr[k][l] = ch;
                                                        }
                                               }
                                        }
                                //      reference check for rect coordinates
                                //      printf("x1=%d,y1=%d,radius=%d\n", cx1, cy1, crad);
                                }
                                //CHAR set up after GRID
                                else if (sscanf(input, "%s %c", command, &ch) && strcmp(command, CHAR) == 0){
                                //      printf("setup char %c successfully\n", ch);
                                }
                                //avoid GRID repeated setup
                                else if (sscanf(input, "%s %d %d", command, &dxaxis, &dyaxis) && strcmp(command, GRID) == 0){
                                        printf("GRID was already set to %d,%d.\n", xaxis, yaxis);
                                }
                                //Invalid Command
                                else if (sscanf(input, "%s %[^\n]%*c", command, error) && strcmp(command, GRID) != 0 && strcmp(command, CHAR) != 0 && strcmp(command, CIRCLE) != 0 && strcmp(command, LINE) != 0 && strcmp(command, RECTANGLE) != 0 && strcmp(command, END) != 0){
                                        printf("Error did not understand %s %s\n", command, error);
                                }
                                //END
                                else if (sscanf(input, "%s", command) && strcmp(command, END) == 0){
                                        break;
                                }
                        }//while loop
                        }//if statement 1000^2
                        else{
                                printf("GRID needs to be less than 1000 x 1000\n");
                        }
                }//if statment GRID
		//CHAR set up before GRID
                else if (sscanf(input, "%s %c", command, &ch) && strcmp(command, CHAR) == 0){
                //      printf("setup char %c successfully\n", ch);
                }
                //END
                else if (sscanf(input, "%s", command) && strcmp(command, END) == 0){
                        break;
                }
                //No other commands allowed except GRID/CHAR/END
                else{
                printf("Only CHAR command is allowed before the grid size is set.\n");}
                }

        return 0;
}

