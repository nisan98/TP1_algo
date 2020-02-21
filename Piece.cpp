/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */
#include <iostream>

#include "Piece.h"
#include "Porte.h"

using namespace std;


namespace TP1
{

/**
* \fn Piece::Piece()
* \brief Constructeur par défaut.
*/
Piece::Piece() :
	m_parcourue(false),
	m_nom(std::string("")),
	m_distanceDuDebut(0) { }


/**
* \fn Piece::Piece(const std::string & p_nom)
* \brief Surcharge du constructeur par défaut, où le nom de la pièce est spécifié.
* \param[in]	string p_nom Le nom de la pièce.
*/
Piece::Piece(const std::string & p_nom) : 
	m_parcourue(false),
	m_nom(p_nom),
	m_distanceDuDebut(0) { }


/**
* \fn Piece::Piece(const Piece & p_source)
* \brief Constructeur copie.
* \param[in]	Piece p_source La pièce à copier.
*/
Piece::Piece(const Piece & p_source) :
	m_portes(p_source.getPortes()), 
	m_parcourue(p_source.getParcourue()),
	m_nom(p_source.getNom()), 
	m_distanceDuDebut(p_source.getDistanceDuDebut()) { }


/**
* \fn Piece::~Piece()
* \brief Destructeur. Vide.
*/
Piece::~Piece() { }


/**
* \fn Piece::getNom() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_nom, le nom de la pièce.
*/
std::string Piece::getNom() const
{
	return m_nom;
}


/**
* \fn Piece::getParcourue() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_parcourue, qui indique si la pièce a été parcourue
* 		 par la méthode Labyrinthe::solutionner.
*/
bool Piece::getParcourue() const
{
	return m_parcourue;
}


/**
* \fn Piece::getPortes() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_portes, la liste des portes de la pièce.
*/
const std::list<Porte> & Piece::getPortes() const
{
	return m_portes;
}


/**
* \fn Piece::getDistanceDuDebut() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_distanceDuDebut, la distance de la pièce par rapport
*  		 à la case départ.
*/
int Piece::getDistanceDuDebut() const
{
	return m_distanceDuDebut;
}


/**
* \fn Piece::ajoutePorte(const Porte & p_porte)
* \brief Ajoute une porte à la liste de portes, m_portes.
* \param[in]	Porte p_porte La porte à ajouter à m_portes.
*/
void Piece::ajoutePorte(const Porte & p_porte)
{
	m_portes.push_back(p_porte);
}


/**
* \fn Piece::setParcourue(bool p_parcourue)
* \brief Associe la valeur de p_parcourue à l'attribut de classe m_parcourue.
* \param[in]	bool p_parcourue True si la pièce a été parcourue, false sinon.
*/
void Piece::setParcourue(bool p_parcourue)
{
	m_parcourue = p_parcourue;
}


/**
* \fn Piece::setDistanceDuDebut(int p_distanceDuDebut)
* \brief Ajuste la valeur de la distance de la pièce par rapport à la case de départ, m_distanceDuDebut.
* \param[in]	int p_distanceDuDebut La distance de la pièce de la case de départ.
*/
void Piece::setDistanceDuDebut(int p_distanceDuDebut)
{
	m_distanceDuDebut = p_distanceDuDebut;
}


/**
* \fn Piece::operator =(const Piece & p_source)
* \brief Surcharge de l'opérateur =. Copie les attributs de classe de p_source.
* \param[in]	Piece p_source La pièce à copier.
*/
const Piece & Piece::operator =(const Piece & p_source) 
{ 
	m_portes = p_source.getPortes();
	m_parcourue = p_source.getParcourue();
	m_nom = p_source.getNom();
	m_distanceDuDebut = p_source.getDistanceDuDebut();
	return *this; 
}


/**
* \fn Piece::afficherPiece() const
* \brief Affiche la valeur des attributs de classe, notamment toutes les portes de la liste de portes, m_portes.
*/
void Piece::afficherPiece() const
{
	cout << "Nom de la pièce : " << getNom() << endl;
	cout << "Distance du début : " << getDistanceDuDebut() << endl;
	cout << "Parcourue : " << getParcourue() << endl;

	unsigned int nbrPorte = 0;
	for (Porte porte : getPortes()) {
		cout << "Porte " << ++nbrPorte << ": ";
		porte.afficherPorte();
	}
}

} // fin du namespace TP1
