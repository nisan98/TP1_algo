/**
 * \file Labyrinthe.cpp
 * \brief Le code des méthodes membres et privés de la classe Labyrinthe.
 * \author IFT-2008, Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 * 
 */

//Fichiers à compléter par les autres méthodes de la classe Labyrinthes demandées
#include <algorithm>
#include <vector>

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


/**
* \fn Labyrinthe::nouvelleListe(Labyrinthe::NoeudListePieces * p_dernier) const
* \brief Fonction qui retourne l'adresse d'un noeud d'une nouvelle liste chaînée circulaire, copiée d'un autre 
* 		 labyrinthe à partir de son membre m_dernier. Ce noeud est assigné à m_dernier du nouveau labyrinthe par 
* 		 le constructeur copie et la fonction de surcharge de l'opérateur =.
* \param[in]	NoeudListePieces p_dernier Le membre m_dernier du labyrinthe à copier.
*/
Labyrinthe::NoeudListePieces * Labyrinthe::nouvelleListe(Labyrinthe::NoeudListePieces * p_dernier) const
{
	Labyrinthe::NoeudListePieces* nouveauDernier = nullptr;
	
	if (p_dernier != nullptr) {
		Labyrinthe::NoeudListePieces* noeudLabyrintheCopie = p_dernier;
		
		do {
			Labyrinthe::NoeudListePieces* noeud = new Labyrinthe::NoeudListePieces;
			noeud->m_piece = noeudLabyrintheCopie->m_piece;

			if (nouveauDernier == nullptr) {
				noeud->m_suivant = noeud;
				nouveauDernier = noeud;
			}
			else {
				noeud->m_suivant = nouveauDernier->m_suivant;
				nouveauDernier->m_suivant = noeud;
			}

			noeudLabyrintheCopie = noeudLabyrintheCopie->m_suivant;
		}
		while(noeudLabyrintheCopie != p_dernier);
	}
	
	return nouveauDernier;
}


/**
* \fn Labyrinthe::Labyrinthe()
* \brief Constructeur par défaut.
*/
Labyrinthe::Labyrinthe() :
	m_dernier(nullptr),
	m_depart(nullptr),
	m_arrivee(nullptr) { }


/**
* \fn Labyrinthe::Labyrinthe(const Labyrinthe & p_source)
* \brief Constructeur copie. Utilise la méthode Labyrinthe::nouvelleListe pour initialiser le membre m_dernier.
* \param[in]	Labyrinthe p_source Le labyrinthe à copier.
*/
Labyrinthe::Labyrinthe(const Labyrinthe & p_source) :
	m_dernier(nouvelleListe(p_source.m_dernier)),
	m_depart(p_source.getDepart()),
	m_arrivee(p_source.getArrivee()) { }


/**
* \fn Labyrinthe::~Labyrinthe()
* \brief Destructeur. Libère la mémoire dynamique associée à chaque noeud de la liste chaînée circulaire.
*/
Labyrinthe::~Labyrinthe() 
{ 
	if (m_dernier != nullptr) {
		Labyrinthe::NoeudListePieces * noeud = m_dernier->m_suivant;
		Labyrinthe::NoeudListePieces * noeudSuivant;

		do {
			noeudSuivant = noeud->m_suivant;
			delete noeud;
			noeud = noeudSuivant;
		}
		while(noeud != m_dernier);

		delete noeud;
	}
}


/**
* \fn Labyrinthe::operator =(const Labyrinthe & p_source)
* \brief Surcharge de l'opérateur =. Utilise la méthode Labyrinthe::nouvelleListe pour copier le membre m_dernier du
 * 		 labyrinthe source.
* \param[in]	Labyrinthe p_source Le labyrinthe à copier.
*/
const Labyrinthe & Labyrinthe::operator =(const Labyrinthe & p_source)
{	
	m_dernier = nouvelleListe(p_source.m_dernier);
	m_depart = p_source.getDepart();
	m_arrivee = p_source.getArrivee();
	return *this;
}


/**
* \fn Labyrinthe::solutionner(Couleur p_joueur)
* \brief Détermine le nombre de déplacements nécessaires au joueur de la couleur p_joueur pour atteindre la case finale.
* \param[in]	Couleur p_joueur La couleur du joueur dont le labyrinthe est solutionné.
*/
int Labyrinthe::solutionner(Couleur p_joueur)
{
	queue<Piece*> filePieces;
	filePieces.push(&(m_dernier->m_piece));
	Piece* pieceDefilee, * pieceDestination;
	int distanceDebutArrivee = -1;
	Labyrinthe::NoeudListePieces * noeud;

	while (!filePieces.empty() && distanceDebutArrivee == -1) {
		pieceDefilee = filePieces.front();

		if (pieceDefilee->getNom() == getArrivee()->getNom()) {
			distanceDebutArrivee = pieceDefilee->getDistanceDuDebut();
		}
		else {
			for (Porte porte : pieceDefilee->getPortes()) {
				pieceDestination = porte.getDestination();
				
				if (!pieceDestination->getParcourue() && porte.getCouleur() == p_joueur) {
					if (pieceDestination->getNom() == getArrivee()->getNom()) {
						distanceDebutArrivee = pieceDefilee->getDistanceDuDebut() + 1;
					}
					else {
						pieceDestination->setParcourue(true);
						pieceDestination->setDistanceDuDebut(pieceDefilee->getDistanceDuDebut() + 1);
						filePieces.push(pieceDestination);
					}
				}
			}

			if (pieceDefilee->getNom() == "0,0") {
				pieceDefilee->setParcourue(true);
			}

			noeud = m_dernier;
			do {
				pieceDestination = &(noeud->m_piece);
				
				for (Porte porte : pieceDestination->getPortes()) {
					if (porte.getDestination()->getNom() == pieceDefilee->getNom() 
							&& !pieceDestination->getParcourue() 
							&& porte.getCouleur() == p_joueur) {
						pieceDestination->setParcourue(true);
						pieceDestination->setDistanceDuDebut(pieceDefilee->getDistanceDuDebut() + 1);
						filePieces.push(pieceDestination);
					}
				}

				noeud = noeud->m_suivant;
			} 
			while(noeud != m_dernier);

			filePieces.pop();
		}
	}

	noeud = m_dernier;
	do {
		noeud->m_piece.setDistanceDuDebut(0);
		noeud->m_piece.setParcourue(false);
		noeud = noeud->m_suivant;
	}
	while(noeud != m_dernier);

	return distanceDebutArrivee;
}


/**
* \fn Labyrinthe::trouveGagnant()
* \brief Détermine la couleur du joueur gagnant à l'aide de la méthode Labyrinthe::solutionner.
*/
Couleur Labyrinthe::trouveGagnant()
{
	vector<Couleur> vecCouleur {Couleur::Rouge, Couleur::Vert, Couleur::Bleu, Couleur::Jaune};
	int solution = -1;
	int solutionTest;
	Couleur gagnant = Couleur::Aucun;

	for (Couleur couleur : vecCouleur) {
		solutionTest = solutionner(couleur);
		
		if (solutionTest != -1) {
			if (solution == -1 || solutionTest < solution) {
				solution = solutionTest;
				gagnant = couleur;
			}
			else if (solutionTest == solution && 
						std::find(vecCouleur.begin(), vecCouleur.end(), couleur) 
						< std::find(vecCouleur.begin(), vecCouleur.end(), gagnant)) {
					gagnant = couleur;
			}
		}
	}

	return gagnant;
}


/**
* \fn Labyrinthe::appartient() const
* \brief Détermine si la pièce p_piece est contenue dans la liste chaînée circulaire du Labyrinthe.
* \param[in] 	Piece p_piece La pièce pour laquelle on cherche à savoir si elle est dans le labyrinthe.
*/
bool Labyrinthe::appartient(const Piece & p_piece) const
{
	bool appartient = false;

	if (m_dernier != nullptr) {
		Labyrinthe::NoeudListePieces * noeud = m_dernier;

		do {
			if (noeud->m_piece.getNom() == p_piece.getNom()) {
				appartient = true;
			}
			else {
				noeud = noeud->m_suivant;
			}
		} 
		while(noeud != m_dernier && !appartient);
	}

	return appartient;
}


/**
* \fn Labyrinthe::placeDepart(const string & p_nom)
* \brief Associe au membre m_depart un pointeur vers la pièce de nom p_nom. Utilise la fonction Labyrinthe::trouvePiece
* 		 pour trouver la pièce appropriée.
* \param[in] 	string p_nom Le nom de la pièce.
*/
void Labyrinthe::placeDepart(const string & p_nom) 
{ 
	m_depart = &(trouvePiece(p_nom)->m_piece);
}


/**
* \fn Labyrinthe::placeArrivee(const string & p_nom)
* \brief Associe au membre m_arrivee un pointeur vers la pièce de nom p_nom. Utilise la fonction Labyrinthe::trouvePiece
* 		 pour trouver la pièce appropriée.
* \param[in] 	string p_nom Le nom de la pièce.
*/
void Labyrinthe::placeArrivee(const string & p_nom)
{ 
	m_arrivee = &(trouvePiece(p_nom)->m_piece);
}


/**
* \fn Labyrinthe::trouvePiece(const string & p_nom) const
* \brief Détermine le noeud de la liste chaînée circulaire contenant la pièce de nom p_nom. Lance une erreur
* 		 invalid_argument si p_nom est vide, et une erreur logic_error si la pièce est introuvable ou si le membre
* 		 m_dernier est un nullptr.
* \param[in] 	string p_nom Le nom de la pièce.
*/
Labyrinthe::NoeudListePieces * Labyrinthe::trouvePiece(const string & p_nom) const
{ 
	if (p_nom.empty()) {
		throw invalid_argument("Labyrinthe::trouvePiece : Le nom de la pièce, p_nom, est vide.");
	}

	if (m_dernier != nullptr) {
		Labyrinthe::NoeudListePieces * noeud = m_dernier;

		do {
			if (noeud->m_piece.getNom() == p_nom) {
				return noeud;
			}
			else {
				noeud = noeud->m_suivant;
			}
		} 
		while(noeud != m_dernier);

		throw logic_error("Labyrinthe::trouvePiece : Pièce introuvable.");
	}
	else {
		throw logic_error("Labyrinthe::trouvePiece : m_dernier est un nullptr.");
	}
}


/**
* \fn Labyrinthe::afficherLabyrinthe() const
* \brief Affiche l'ensemble des pièces contenues dans la liste chaînée circulaire, ainsi que les attributs de classe.
*/
void Labyrinthe::afficherLabyrinthe() const
{
	Labyrinthe::NoeudListePieces * noeud = m_dernier;
	unsigned int nbrNoeud = 0;

	cout << "Pièce de départ : " << getDepart()->getNom() << endl;
	cout << "Pièce d'arrivée : " << getArrivee()->getNom() << endl;
	cout << "Pièce de m_dernier : " << m_dernier->m_piece.getNom() << endl;
	cout << endl;

	do {
		cout << "Noeud " << ++nbrNoeud << endl;

		noeud->m_piece.afficherPiece();
		cout << endl;
		noeud = noeud->m_suivant;
	} 
	while(noeud != m_dernier);
}

} // fin du namespace TP1
