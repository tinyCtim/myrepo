
/* tspeek.c - lrb */

#include "ts.h"

void paws (n) int n; {
  int i,j,k;
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
      for (k=0;k<n;k++) ;
}

char sak(s) char *s; { /* 2.2k */
  printf("%s",s);
  return (getchar());
}

int index(s,t) char s[],t[]; { /* return index of t in s, -1 if none */
  int i,j,k;
  for (i=0;s[i]!='\0';i++) {
    for (j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++) ;
    if (t[k]=='\0') return(i);
    }
  return(-1);
}

int getline(s,lim) char s[]; int lim; {
/* get line into s, return length */
  int c,i;
  i=0;
  while (--lim>0 && (c=getchar()) != EOF && c != '\n') s[i++]=c;
  s[i]='\0';
  return(i);
}

int wurds; /* 2.2l */
char swurds[5]; /* 2.2l */
int gct; /* 2.2j 2.2l */

void main(argc,argv) int argc;char *argv[]; {
  char *ptr;
  int actr;
  int fpti;
  char tail[20];
  char wmk[200];
  char tfo[32],tfh[32];
  char c;
  int i,j,fpt,fpt1;
  char wwws[40],wws[40],ws[40],sws[40];
  int idx;
  char cs[2];
  char special[23];
  cs[1]='\0'; /* 2.2j */
  strcpy(special,"\",.?!;:<>)(");  /* 2.2g */
  strcpy(crlf,"\r\n");
  strcpy(lf,"\n");
  strcpy(ver,"2.2o"); /* 2.2o */
  wurds=0; /* 2.2l */
  gct=0; /* 2.2l */
  printf("\n%s%s","\nToby Speak Version ",ver);
  printf("%s"," (c) 2008, Lee Bradley");
  untran=verbose=0;
  actr=argc;
  if (argc==1) {
    printf("\n\n-v -u filename.typ ");
    if (!getline(tail,100)) i_error();
    if (index(tail,"-v")==-1 && index(tail,"-u")==-1) ;
    else {
      if (index(tail,"-v")!=-1) verbose=1;
      if (index(tail,"-u")!=-1) untran=1;
      for (i=strlen(tail);i>0 && tail[i]!=' ';i--) ;
      if (i==0) i_error();
      strcpy(tail,tail+i+1);
      }
    }
  else {
    while (actr>=3) {
      actr--;
      ptr = argv[argc-actr];
      if (*ptr++ != '-') i_error();
      switch (tolower(*ptr++)) {
        case 'v': verbose = 1;continue;
        case 'u': untran = 1;continue;
        default: i_error();
        }
      }
    if (actr<2) i_error();
    strcpy(tail,argv[argc-1]);
    }
  if (index(tail,"-")==0) i_error(); 
  printf("\n");
  strcpy(tdf,"tobee.dic");
  loaddic();
  strcpy(tf,tail);
  i=0;
  if ((fpti=fopen(tf,"r"))==NULL) {
    printf("\nCan't open %s\n",tf);
    i_error();
    }
  while ((c=fgetc(fpti))!=EOF) {
    cs[0]=c;
    /* pad double-quote, comma, etc. w/ spaces */
    if (index(special,cs)!=-1) {tt[i++]=' ';tt[i++]=c;tt[i++]=' ';}
    /* replace cr/lf w/ space followed by newline */
    if (c=='\n') {tt[i++]=' ';tt[i++]='\n';}
    if (index(crlf,cs)==-1 && index(special,cs)==-1) {tt[i++]=c;}
    }
  tt[i]='\0'; /* just to be safe ... */ /* 2.2j */
  /* replace -> w/ == to prevent translation */ /* 2.2j */
  while ((i=index(tt,"- > "))!=-1) {
    strcpy(ntt,tt);ntt[i]='\0';strcat(ntt,"==");   
    strcat(ntt,tt+i+4);strcpy(tt,ntt);
    }
  fclose(fpti);
  strcpy(ntt,"");
  while (vl!=-2) {
    trantobee();
    if (vl==-1) vl=-2;
    else {
      strcpy(tt,ntt);strcpy(ntt,"");
      strcpy(tdf,tdfnext);
      loaddic();
      }
    }
  /* bring back any -> */ /* 2.2j */
  while ((i=index(ntt,"=="))!=-1) {
    strcpy(tt,ntt);tt[i]='\0';strcat(tt,"->");   
    strcat(tt,ntt+i+2);strcpy(ntt,tt);
    }
  /* 2.2j */
  printf("\n\nYour (un)translation follows ...");
  sak("\n\nStrike Any Key ...\n");
  j=i=0; /* 2.2k */
  while (c=ntt[i++]) {
    /* remove space padding around double-quotes, comma etc. */
    cs[0]=ntt[i];
    if (c==' ' && index(special,cs)!=-1 && ntt[i+1]==' ') {
      c=ntt[i];i+=2;
      }
    putchar(c);
    if (c=='\n') { /* 2.2k */
      j++;if (j==20) {j=0;sak("\nStrike Any Key ...\n");}
      }    
    }
  printf("\n");
  strcpy(msg,"x+=\""); /* 2.2l */
  strcpy(wwws,"still->ztill");
  if (!untran) strcpy(wmk,"\nTranslation by ");
  else strcpy(wmk,"\nUntranslation by ");
  strcat(wmk,"Toby Speak Version ");strcat(wmk,ver);
  strcat(wmk,"\n");
  strcat(wmk,"The dishunary contains ");
  sprintf(swurds,"%d",wurds); /* 2.2l */
  strcat(wmk,swurds);strcat(wmk," wurds.\n"); /* 2.2l */
  strcat(wmk,lf);strcat(ntt,wmk);
  i=index(tf,".");
  if (i==-1) {strcat(tf,".");i=index(tf,".");}
  strcpy(tfo,tf);strcpy(tfh,tf);tfo[i]=tfh[i]='\0';	
  if (!untran) strcat(tfo,".tbo");else strcat(tfo,".txt");
  strcat(tfh,".htm");
  if ((fpt = fopen(tfo,"w")) == NULL) {
    printf("\nCan't open %s\n",tfo);
    i_error();
    }
  if ((fpt1 = fopen(tfh,"w")) == NULL) {
    printf("\nCan't open %s\n",tfh);
    i_error();
    }
  if (gct) { /* 2.2j */
    printf("\n\nYour (un)translation follows ...");
    sak("\n\nStrike Any Key ...\n");
    } 
  j=i=0; /* 2.2k */
  while (c=ntt[i++]) {
    /* remove space padding around double-quotes, comma etc. */
    cs[0]=ntt[i];
    if (c==' ' && index(special,cs)!=-1 && ntt[i+1]==' ') {
      c=ntt[i];i+=2;
      }
    fputc(c,fpt);fputc(c,fpt1);if (gct) putchar(c);
    if (c=='\n') { /* 2.2k */
      j++;if (j==20 && gct) {j=0;sak("\nStrike Any Key ...\n");}
      }    
    }
  fclose(fpt);fclose(fpt1);   
  printf("\n%s%s%s%s%s\n\n","See ",tfo," and ",tfh," for output.");
}

void loaddic() {
  int i;
  char c;
  if ((fpd = fopen(tdf,"r")) == NULL) {
    printf("\nCan't open %s\n",tdf);
    exit();
    }
  i=0;strcpy(td,"");
  while ((c = fgetc(fpd)) != EOF) {
    if (c == '\r' || c == '\n') ; else td[i++]=c;
    if (c=='~' && gct==0) wurds+=1; /* 2.2l */
    }
  td[i]='\0';
  fclose(fpd);
  vl=index(td,"|");
  if (vl!=-1) {
    for (i=vl+1;td[i]!=']';++i) tdfnext[i-vl-1]=td[i];
    tdfnext[i-vl-1]='\0';
    }
}

void trantobee() {
/* (un)translate text in tt to tobee using dictionary */
  gi=0;
  endoffile=0;
  while (!endoffile) doit();
}

void doit() { /* main loop - extract word from input file */
  int dp; /* dictionary position */
  int cap;
  int n,nc;
  int csw;
  char wws[100],ws[100];
  int j;
  char scs[10],scsw[1];
  char fus[100];
  char c;
  int lgi;
  n=index(tt+gi," ");
  nc=index(tt+gi,lf);
  if (n==0 && nc==1) { /* space followed by newline */
    strcat(ntt,lf);gi+=2;
    }
  else if (nc==0) { /* newline */
    strcat(ntt,lf);gi+=1;
    }
  else {
    lgi=gi;
    for (j=0;j<n;++j) {
      ws[j]=wws[j]=tt[lgi];lgi++;
      }
    ws[j]=wws[j]='\0';
    if (!untran) strcpy(fus,"_"); else strcpy(fus,"~");
    strcat(fus,wws);strcat(fus,"_");strcpy(wws,fus);
  /* find word in dictionary */
  /* lower case but remember case */
    cap=0;
    if (ws[0]>='A' && ws[0]<='Z') {
      cap=1;ws[0]=ws[0]+' ';wws[1]=wws[1]+' ';
      }
    dp=index(td,wws); /* dictionary position of word */
    if (dp==-1) { /* not in dictionary */
      if (cap) ws[0]=ws[0]-' ';
      }
    else { /* in dictionary */
      if (!untran) {
        dp+=strlen(wws)+3; /* get past word and ->~ */
        }
      else {
        dp-=4; /* back up to last letter of original word */
        j=0;
        while (td[dp+j]!='_') --j;
        dp+=j+1; 
        }
      j=0;  
      while (td[dp+j]!='_') {ws[j]=td[dp+j];++j;}
      ws[j]='\0';
      if (cap && ws[0]>='a' && ws[0]<='z') ws[0]=ws[0]-' ';
      }
  /* put (un)translated (or unchanged) word (etc.) in output array */
    strcat(ws," "); 
    strcat(ntt,ws); 
    if (dp!=-1 && verbose) { /* show word and (un)translation */
      /* trash _ in source */
      wws[strlen(wws)-1]='\0';if (cap) wws[1]=wws[1]-' ';
      printf("%s%s%s\n",wws+1," -> ",ws);paws(200);
      }
    }
  /* advance pointer in input file */
    if (nc==0) ;
    else if (n!=nc-1) gi+=n+1;
    else gi+=n;
    if (tt[gi]=='\0' || n==-1) endoffile=1;
}

void i_error() {
  printf("\nTranslate English to Toby Speak ");
  printf("or \"Untranslate\" Toby Speak to English");
  printf("\n\nUsage: tspeek -v -u filename.typ");
  printf("\n-v gives verbose reporting");
  printf("\n-u \"untranslate\" Toby Speak to English");
  printf("\nDefault is translate English to Toby Speak");
  sak("\n\nStrike Any Key ...\n");
  exit();
}

