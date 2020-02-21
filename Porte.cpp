/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */
#include <iostream>

#include "Porte.h"
#include "Piece.h"

using namespace std;


namespace TP1
{

/**
* \fn Porte::Porte()
* \brief Constructeur par défaut.
*/
Porte::Porte() :
	m_destination(nullptr),
	m_couleur(Couleur::Aucun) { }


/**
* \fn Porte::Porte(Couleur p_couleur, Piece* p_destination)
* \brief Surcharge du constructeur par défaut, où la couleur de la porte et le pointeur de la pièce de destination
* 		 sont spécifiés.
* \param[in]	Couleur p_couleur La couleur de la porte.
* \param[in]	Piece* p_destination Le pointeur vers la pièce de destination.
*/
Porte::Porte(Couleur p_couleur, Piece* p_destination) : 
	m_couleur(p_couleur), 
	m_destination(p_destination) { }


/**
* \fn Porte::Porte(const Porte & p_porte)
* \brief Constructeur copie.
* \param[in]	Porte p_porte La porte à copier.
*/
Porte::Porte(const Porte & p_porte) :
	m_couleur(p_porte.getCouleur()), 
	m_destination(p_porte.getDestination()) { }


/**
* \fn Porte::~Porte()
* \brief Destructeur. Vide.
*/
Porte::~Porte() { }


/**
* \fn Porte::getCouleur() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_couleur, le couleur de la porte.
*/
Couleur Porte::getCouleur() const
{
	return m_couleur;
}


/**
* \fn Porte::getDestination() const
* \brief Permet d'obtenir la valeur de l'attribut de classe m_destination, le pointeur vers la pièce de destination.
*/
Piece* Porte::getDestination() const
{
	return m_destination;
}


/**
* \fn Porte::operator ==(const Porte & p_source) const
* \brief Compare deux portes. Retourne true si les attributs de classe sont identiques un à un.
* \param[in]	Porte p_source La porte utilisée pour la comparaison.
*/
bool Porte::operator ==(const Porte & p_source) const
{
	return (m_couleur == p_source.getCouleur()) && (m_destination == p_source.getDestination());
}


/**
* \fn Porte::operator =(const Porte & p_source)
* \brief Surcharge de l'opérateur =. Copie les attributs de classe de p_source.
* \param[in]	Porte p_source La porte à copier.
*/
const Porte & Porte::operator =(const Porte & p_source)
{ 
	m_destination = p_source.getDestination();
	m_couleur = p_source.getCouleur();
	return *this;
}


/**
* \fn Porte::afficherPorte() const
* \brief Affiche la valeur des attributs de classe.
*/
void Porte::afficherPorte() const
{
	cout << "couleur ";

	switch (getCouleur()) {
		case Couleur::Rouge : cout << "rouge, "; break;
		case Couleur::Vert : cout << "verte, "; break;
		case Couleur::Bleu : cout << "bleue, "; break;
		case Couleur::Jaune : cout << "jaune, "; break;
		default : cout << "aucune, ";
	}

	cout << "pièce de destination " << getDestination()->getNom() << endl;
}

} // fin du namespace TP1
