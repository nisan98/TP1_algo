/**
 * \file Piece.h
 * \brief Ce fichier contient l'interface d'une pièce.
 * \author IFT-2008
 * \version 0.1
 * \date janvier 2020
 *
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <string>    // Pour le nom de la pièce
#include <list>	     // Pour utiliser la liste de la STL

#include "Porte.h"

namespace TP1
{
/**
 *  \class Piece
 *  \brief Classe représentant une pièce dans un labyrinthe
 */
class Piece
{
public:

	//! Constructeur par défaut
	Piece();

	//! Surcharge du constructeur
	Piece(const std::string & p_nom);

	//! Constructeur de copie
	Piece(const Piece & p_source);

    //! Destructeur
	~Piece();

    //! Surcharge de l'opérateur =
	const Piece & operator=(const Piece & p_source);

    //! Accesseur du nom d'une pièce
	std::string getNom() const;

    //! Pour initialiser l'attribut parcourue à true ou false
	void setParcourue(bool p_parcourue);

    //! Pour initialiser l'attribut distanceDuDebut
	void setDistanceDuDebut(int p_distanceDuDebut);

	//! Accéder au membre parcourue
	bool getParcourue() const;

	//! Accéder à la liste des portes qui partent de la pièce
	const std::list<Porte> & getPortes() const;

    //! Accéder au membre distanceDuDebut
	int getDistanceDuDebut() const;

    //! Ajouter une porte à la liste des portes qui partent de la pièce
	void ajoutePorte(const Porte & p_porte);

	//! Affiche la valeur des attributs de classe.
	void afficherPiece() const;

private:
	std::list<Porte> m_portes; /*!< Les portes qui partent de la pièce. */
	/*!< Cette liste peut ne pas contenir toutes les portes qui
	communiquent avec la pièce. Une partie de ces portes peut être placée dans la liste de portes
	de l'autre pièce associée à la porte.*/

	bool m_parcourue; /*!< Indique si la pièce a été parcourue*/
	/*!< Le champ "parcourue" sert uniquement à la méthode solutionner() de la classe labyrinthe, afin de ne pas passer
	plusieurs fois par une même pièce et risquer de tourner en rond, et donc boucler sans fin. */

	std::string m_nom; /*!< Le nom de la pièce. Il doit être unique pour un même labyrinthe.*/

	int m_distanceDuDebut; /*!< Le nombre de déplacements qu'il est nécessaire d'effectuer depuis la pièce de départ pour se rendre à cette pièce. */

};

} // fin du namespace TP1

#endif /* PIECE_H_ */
