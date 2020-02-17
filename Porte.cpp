/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */

#include "Porte.h"


namespace TP1
{

// À compléter
Porte::Porte() { }

Porte::Porte(Couleur p_couleur, Piece* p_destination) : 
	m_couleur(p_couleur), 
	m_destination(p_destination) { }

Porte::Porte(const Porte & p_porte) :
	m_couleur(p_porte.getCouleur()), 
	m_destination(p_porte.getDestination()) { }

// À compléter
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
	return (m_couleur == p_source.getCouleur()) & (m_destination == p_source.getDestination());
}

// À compléter
const Porte & Porte::operator =(const Porte & p_source) { return *this; }

}
