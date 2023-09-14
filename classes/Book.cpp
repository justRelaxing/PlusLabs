#include "Book.h"

Book::Book(const std::string& title, Binding binding, Edition edition, Quality quality) :
	m_title(title), m_binding(binding), m_edition(edition), m_quality(quality) {}

Binding Book::getBinding() {

	return m_binding;
}

Edition Book::getEdition() {

	return m_edition;
}

Quality Book::getQuality() {

	return m_quality;
}

std::string Book::getTitle() {

	return m_title;
}
