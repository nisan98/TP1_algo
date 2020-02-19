/**
 * \file Labyrinthe.cpp
 * \brief Le code des méthodes membres et privés de la classe Labyrinthe.
 * \author IFT-2008, Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 * 
 */

//Fichiers à compléter par les autres méthodes de la classe Labyrinthes demandées

#include "Labyrinthe.h"

using namespace std;

namespace TP1
{
// -------------------------------------------------------------------------------------------------
//	Méthodes fournies
// -------------------------------------------------------------------------------------------------

/**
* \fn Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream & entree)
* \brief Fonction déjà fournie permettant de charger un labyrinthe depuis un fichier
* \param[in] couleur La couleur du jouer auquel le labyrinthe chargé s'applique
* \param[in] entree Fichier contenant la définition du labyrinthe
*/
void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream& entree)
{
 int nbCols, nbRangs;

 if (!entree.is_open())
	 throw logic_error("Labyrinthe::chargeLabyrinthe: Le fichier n'est pas ouvert !");

 entree >> nbCols >> nbRangs;
 entree.ignore(); // Pour consommer le \n (le caractère fin de ligne)

 const int MAX_LIGNE = 1000;
 char ligne[MAX_LIGNE];

 entree.getline(ligne, MAX_LIGNE);
 entree.getline(ligne, MAX_LIGNE);

 std::ostringstream s; // Une chaîne pour écrire dedans, cette chaîne servira pour nommer les pièces du labyrinthe

 for (int i = 0; i < nbCols; i++)
 {
	 for (int j = 0; j < nbRangs; j++)
	 {
		 s << i << "," << j;
		 Piece p(s.str());
		 s.str("");
		 ajoutePieceLabyrinthe(p);
	 }
 }

 for (int i = 0; i < nbCols; i++)
 {
	 if (ligne[i * 4 + 1] == 'D' || ligne[i * 4 + 1] == 'd')
	 {
		 std::string nom;
		 s << i << ",0";
		 nom = s.str();
		 s.str("");
		 placeDepart(nom);
	 }
	 if (ligne[i * 4 + 1] == 'F' || ligne[i * 4 + 1] == 'f' || ligne[i * 4
		 + 1] == 'A' || ligne[i * 4 + 1] == 'a')
	 {
		 std::string nom;
		 s << i << ",0";
		 nom = s.str();
		 s.str("");
		 placeArrivee(nom);
	 }
 }

 for (int j = 0; j < nbRangs; j++)
 {
	 entree.getline(ligne, MAX_LIGNE);

	 for (int i = (j == nbRangs - 1 && (j & 1)) ? 1 : 0; i < nbCols; i++)
	 {
		 if (j & 1)
		 {
			 if (j < nbRangs - 2 && ligne[i * 4 + 3] == ' ')
			 {
				 ajoutePassage(couleur, i, j, i, j + 2);
			 }
			 if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
			 {
				 ajoutePassage(couleur, i, j, i, j + 1);
			 }
			 if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
			 {
				 ajoutePassage(couleur, i - 1, j, i, j + 1);
			 }
			 if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'D' || ligne[i * 4
				 + 1] == 'd'))
			 {
				 std::string nom;
				 s << i << "," << j + 1;
				 nom = s.str();
				 s.str("");
				 placeDepart(nom);
			 }
			 if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'F' || ligne[i * 4
				 + 1] == 'f' || ligne[i * 4 + 1] == 'A' || ligne[i * 4
				 + 1] == 'a'))
			 {
				 std::string nom;
				 s << i << "," << j + 1;
				 nom = s.str();
				 s.str("");
				 placeArrivee(nom);
			 }
		 }
		 else
		 {
			 if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
			 {
				 ajoutePassage(couleur, i - 1, j + 1, i, j);
			 }
			 if (j < nbRangs - 2 && ligne[i * 4 + 1] == ' ')
			 {
				 ajoutePassage(couleur, i, j, i, j + 2);
			 }
			 if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
			 {
				 ajoutePassage(couleur, i, j, i, j + 1);
			 }
			 if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'D' || ligne[i * 4
				 + 3] == 'd'))
			 {
				 std::string nom;
				 s << i << "," << j + 1;
				 nom = s.str();
				 s.str("");
				 placeDepart(nom);
			 }
			 if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'F' || ligne[i * 4
				 + 3] == 'f' || ligne[i * 4 + 3] == 'A' || ligne[i * 4
				 + 3] == 'a'))
			 {
				 std::string nom;
				 s << i << "," << j + 1;
				 nom = s.str();
				 s.str("");
				 placeArrivee(nom);
			 }
		 }
	 }
 }
}


/**
* \fn Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
* \brief Fonction déjà fournie permettant d'ajouter une porte à une pièce
* \param[in]	Couleur couleur Couleur de la porte à ajouter
* \param[in]	int i1
* \param[in]	int j1
* \param[in]	int i2
* \param[in]	int j2
*/
void Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
{

 NoeudListePieces* piece1, * piece2;
 string nomPiece1, nomPiece2;
 ostringstream s;

 s << i1 << "," << j1;
 nomPiece1 = s.str();

 s.str("");

 s << i2 << "," << j2;
 nomPiece2 = s.str();

 s.str("");

 piece1 = trouvePiece(nomPiece1);
 piece2 = trouvePiece(nomPiece2);

 Porte nouvellePorte(couleur, &(piece2->m_piece));

 piece1->m_piece.ajoutePorte(nouvellePorte);
}


/**
* \fn Labyrinthe::ajoutePieceLabyrinthe(Piece & p)
* \brief Fonction déjà fournie permettant d'ajouter une pièce au labyrinthe (si elle ne s'y trouve pas déjà)
* \param[in]	p La pièce à ajouter
* \post	La pièce appartient au labyrinthe;
*/
void Labyrinthe::ajoutePieceLabyrinthe(const Piece& p)
{
 Labyrinthe::NoeudListePieces* noeud = new Labyrinthe::NoeudListePieces;
 noeud->m_piece = p;

 if (m_dernier == nullptr)
 {
	 noeud->m_suivant = noeud;
	 m_dernier = noeud;
 }
 else if (!appartient(p)) {
	 noeud->m_suivant = m_dernier->m_suivant;
	 m_dernier->m_suivant = noeud;
 }
}



Labyrinthe::Labyrinthe() :
	m_dernier(nullptr),
	m_depart(nullptr),
	m_arrivee(nullptr)
	{ }


// Il manque l'initialisation de la liste à partir de m_dernier
Labyrinthe::Labyrinthe(const Labyrinthe & p_source) :
	m_depart(p_source.getDepart()),
	m_arrivee(p_source.getArrivee())
	{ }


Labyrinthe::~Labyrinthe() 
{ 
	Labyrinthe::NoeudListePieces * noeud = m_dernier;
	Labyrinthe::NoeudListePieces * noeud_suivant;

	while (noeud) {
		noeud_suivant = noeud->m_suivant;
		delete noeud;
		noeud = noeud_suivant;
	}
}


// Il manque la copie de m_dernier
const Labyrinthe & Labyrinthe::operator =(const Labyrinthe & p_source)
{	
	m_depart = p_source.getDepart();
	m_arrivee = p_source.getArrivee();
	return *this;
}


int Labyrinthe::solutionner(Couleur joueur)
{
	return -2;
}


Couleur Labyrinthe::trouveGagnant()
{
	return Couleur::Jaune;
}


bool Labyrinthe::appartient(const Piece & p_piece) const
{
	bool appartient = false;

	if (m_dernier != nullptr) {
		Labyrinthe::NoeudListePieces * noeud = m_dernier->m_suivant;

		while (noeud != m_dernier && noeud->m_piece.getNom() != p_piece.getNom()) {
			noeud = noeud->m_suivant;
		}

		if ((noeud == m_dernier && noeud->m_piece.getNom() == p_piece.getNom()) 
				|| noeud != m_dernier) {
			appartient = true;
		}
	}

	return appartient;
}


void Labyrinthe::placeDepart(const std::string & p_nom) 
{ 
	m_depart = &(trouvePiece(p_nom)->m_piece);
}


void Labyrinthe::placeArrivee(const std::string & p_nom)
{ 
	m_arrivee = &(trouvePiece(p_nom)->m_piece);
}


Labyrinthe::NoeudListePieces * Labyrinthe::trouvePiece(const std::string & p_nom) const
{ 
	if (p_nom.empty()) {
		throw invalid_argument("Labyrinthe::trouvePiece : Le nom de la pièce, p_nom, est vide.");
	}

	if (m_dernier != nullptr) {
		Labyrinthe::NoeudListePieces * noeud = m_dernier->m_suivant;
		
		while (noeud != m_dernier && noeud->m_piece.getNom() != p_nom) {
			noeud = noeud->m_suivant;
		}

		if ((noeud == m_dernier && noeud->m_piece.getNom() == p_nom) || noeud != m_dernier) {
			return noeud;
		}
		else {
			throw logic_error("Labyrinthe::trouvePiece : Pièce introuvable.");
		}
	}
	else {
		throw logic_error("Labyrinthe::trouvePiece : m_dernier est un nullptr.");
	}
}

} // fin du namespace TP1
