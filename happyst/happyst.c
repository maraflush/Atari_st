// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 11/02/2020                              *
// * Fonction ........... Fonction dev pour Atari Ste GCC mint    *
// ****************************************************************


// ====================
// * Fichier includes *
// ====================
// #include "header/include.h"
#include "header/happyst.h"


// ==================================
// * Declaration des variables glob *
// ==================================
long* Save_Ecran_Phys;
long* Save_Ecran_Log;
int   Save_Ecran_Mode_Video;
short Save_Buffer_Palette[16];
unsigned char picture_buffer[32034];



// ===================
// * Bip Clavier Off *
// ===================
void bip_clavier_off() 
{
   /* Supexec :
    * https://freemint.github.io/tos.hyp/en/xbios_special.html#Supexec
    */
   Supexec(clavier_off); 
}
 
// ==================
// * Bip Clavier On *
// ==================
void bip_clavier_on() 
{
  /* Supexec :
   * https://freemint.github.io/tos.hyp/en/xbios_special.html#Supexec
   */
  Supexec(clavier_on);
}

// =======================
// * Bip Clavier routine *
// =======================
void clavier_off() 
{
   /* CONTERM :
    * http://retrospec.sgn.net/users/tomcat/miodrag/Atari_ST/Atari%20ST%20Internals.htm
    */
   CONTERM &= 0xFE;
}
 
void clavier_on() 
{
  /* CONTERM :
   * http://retrospec.sgn.net/users/tomcat/miodrag/Atari_ST/Atari%20ST%20Internals.htm
   */
  CONTERM |= 0x01;
}



// ================
// * save_init_st *
// ================
void save_init_st()
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char i;
  
  // ---------------------------
  // * Sauvegarder les données *
  // ---------------------------
  Save_Ecran_Phys = Physbase();
  Save_Ecran_Log = Logbase();
  Save_Ecran_Mode_Video = Getrez();

  // -------------------------------------
  // * Sauvegarder la palette de couleur *
  // -------------------------------------
  for (i=0;i<16;i++)
  {
    /* Setcolor :
     * https://freemint.github.io/tos.hyp/en/Screen_functions.html#Setcolor
     */
    Save_Buffer_Palette[i] = Setcolor(i,-1);
  }

}

// ===================
// * restore_init_st *
// ===================
void restore_init_st()
{
  /* Setscreen :
   * https://freemint.github.io/tos.hyp/en/Screen_functions.html#Setscreen
   */
  Setscreen(Save_Ecran_Phys,Save_Ecran_Log,Save_Ecran_Mode_Video);
  /* Setpalette :
   * https://freemint.github.io/tos.hyp/en/Screen_functions.html#Setpalette
   */
  Setpalette(Save_Buffer_Palette);
  Vsync();
}

// ================
// * Load Picture *
// ================
void load_picture(char* name)
{
  unsigned char id_image;
  // -------------------------
  // * Chargement de l'image *
  // -------------------------
  /* Fopen :
   * https://freemint.github.io/tos.hyp/en/gemdos_file.html#Fopen
   */
  id_image = Fopen(name,0);
  
  // -------------------------------
  // * Placer les donnés en buffer *
  // -------------------------------
  /* Fread :
   * https://freemint.github.io/tos.hyp/en/gemdos_file.html#Fread
   */
  Fread(id_image,32034,picture_buffer);

  // ---------------------
  // * Fermer le fichier *
  // ---------------------
  /* Fclose :
   * https://freemint.github.io/tos.hyp/en/gemdos_file.html#Fclose
   */
  Fclose(id_image);

  // ------------------------------------------
  // * Configuration de la palette de couleur *
  // ------------------------------------------
  /* Setpalette :
   * https://freemint.github.io/tos.hyp/en/Screen_functions.html#Setpalette
   */
  Setpalette(picture_buffer+2);

  // ---------------------------------------
  // * Afficher l'image à l'écran physique *
  // ---------------------------------------
  /* Phybase :
   * https://freemint.github.io/tos.hyp/en/Screen_functions.html#Physbase
   */
  memcpy(Physbase(),picture_buffer+34,32034-34);
}


// ================
// * Get Keyboard *
// ================

short get_keyboard()
{
  short id_key;

  /* Cconis :
   * https://freemint.github.io/tos.hyp/en/gemdos_chrinout.html#Cconis
   */
  if(Cconis()!= 0)
  {
    /* Crawcin :
     * https://freemint.github.io/tos.hyp/en/gemdos_chrinout.html#Crawcin
     */
    id_key = Crawcin()>>16; 
  }

  // Vsync();
  return id_key;
}

// ====================
// * Afficher du text *
// ====================
void draw_text(unsigned char position_x,unsigned char position_y,char* texte,unsigned char couleur)
{
  printf( CURS_LOC, 32+position_y, 32+position_x ); fflush(stdout);
  printf(CHAR_COLOR , couleur);fflush(stdout);
  /* Cconws :
   * https://freemint.github.io/tos.hyp/en/gemdos_chrinout.html#Cconws
   */
  Cconws(texte);
}
