/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */

#include "Piece.h"

namespace TP1
{

Piece::Piece() :
	m_parcourue(false),
	m_nom(std::string("")),
	m_distanceDuDebut(0) { }


Piece::Piece(const std::string & p_nom) : 
	m_parcourue(false),
	m_nom(p_nom),
	m_distanceDuDebut(0) { }


Piece::Piece(const Piece & p_source) :
	m_portes(p_source.getPortes()), 
	m_parcourue(p_source.getParcourue()),
	m_nom(p_source.getNom()), 
	m_distanceDuDebut(p_source.getDistanceDuDebut()) { }


Piece::~Piece() { }


std::string Piece::getNom() const
{
	return m_nom;
}


bool Piece::getParcourue() const
{
	return m_parcourue;
}


const std::list<Porte> & Piece::getPortes() const
{
	return m_portes;
}


int Piece::getDistanceDuDebut() const
{
	return m_distanceDuDebut;
}


void Piece::ajoutePorte(const Porte & p_porte)
{
	m_portes.push_back(p_porte);
}


void Piece::setParcourue(bool p_parcourue)
{
	m_parcourue = p_parcourue;
}


void Piece::setDistanceDuDebut(int p_distanceDuDebut)
{
	m_distanceDuDebut = p_distanceDuDebut;
}


const Piece & Piece::operator =(const Piece & p_source) 
{ 
	m_portes = p_source.getPortes();
	m_parcourue = p_source.getParcourue();
	m_nom = p_source.getNom();
	m_distanceDuDebut = p_source.getDistanceDuDebut();
	return *this; 
}

} // fin du namespace TP1
