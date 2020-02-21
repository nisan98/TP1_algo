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

Porte::Porte() :
	m_destination(nullptr),
	m_couleur(Couleur::Aucun) { }


Porte::Porte(Couleur p_couleur, Piece* p_destination) : 
	m_couleur(p_couleur), 
	m_destination(p_destination) { }


Porte::Porte(const Porte & p_porte) :
	m_couleur(p_porte.getCouleur()), 
	m_destination(p_porte.getDestination()) { }


Porte::~Porte() { }


Couleur Porte::getCouleur() const
{
	return m_couleur;
}


Piece* Porte::getDestination() const
{
	return m_destination;
}


bool Porte::operator ==(const Porte & p_source) const
{
	return (m_couleur == p_source.getCouleur()) && (m_destination == p_source.getDestination());
}


const Porte & Porte::operator =(const Porte & p_source) 
{ 
	m_destination = p_source.getDestination();
	m_couleur = p_source.getCouleur();
	return *this;
}

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
