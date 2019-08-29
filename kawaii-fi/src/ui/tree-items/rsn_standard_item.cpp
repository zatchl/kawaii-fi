#include "rsn_standard_item.h"

#include <QChar>
#include <QList>
#include <QStandardItem>
#include <QString>
#include <QVector>
#include <array>
#include <cstdint>
#include <libkawaii-fi/ies/robust_security_network.h>
#include <libkawaii-fi/security.h>

namespace {
	QList<QStandardItem *> oui_row(const std::array<std::uint8_t, 3> &oui)
	{
		QString oui_string = QString("%0:%1:%2")
		                             .arg(oui[0], 2, 16, QChar('0'))
		                             .arg(oui[1], 2, 16, QChar('0'))
		                             .arg(oui[2], 2, 16, QChar('0'))
		                             .toUpper();
		return {new QStandardItem("OUI"), new QStandardItem(oui_string)};
	}

	QList<QStandardItem *> cipher_type_row(CipherSuiteType cipher_suite_type)
	{
		switch (cipher_suite_type) {
		case CipherSuiteType::SameAsGroupCipher:
			return {new QStandardItem("Cipher Suite Type"),
			        new QStandardItem("Same As Group Cipher")};
		case CipherSuiteType::WEP40:
			return {new QStandardItem("Cipher Suite Type"), new QStandardItem("WEP-40")};
		case CipherSuiteType::TKIP:
			return {new QStandardItem("Cipher Suite Type"), new QStandardItem("TKIP")};
		case CipherSuiteType::CCMP:
			return {new QStandardItem("Cipher Suite Type"), new QStandardItem("CCMP")};
		case CipherSuiteType::WEP104:
			return {new QStandardItem("Cipher Suite Type"), new QStandardItem("WEP-104")};
		}
		return {new QStandardItem("Cipher Suite Type"), new QStandardItem("WEP-40")};
	}

	QList<QStandardItem *> akm_suite_row(AkmSuiteType akm_suite_type)
	{
		switch (akm_suite_type) {
		case AkmSuiteType::IEEE_8021X:
			return {new QStandardItem("AKM Suite Type"), new QStandardItem("802.11X")};
		case AkmSuiteType::PSK:
			return {new QStandardItem("AKM Suite Type"), new QStandardItem("PSK")};
		default:
			return {new QStandardItem("AKM Suite Type"), new QStandardItem("None")};
		}
	}
} // namespace

RsnStandardItem::RsnStandardItem(const RobustSecurityNetwork &rsn)
    : QStandardItem("Robust Security Network")
{
	appendRow({new QStandardItem("Version"), new QStandardItem(QString::number(rsn.version()))});

	QStandardItem *group_cipher_suite_item = new QStandardItem("Group Cipher Suite");
	CipherSuite group_cipher_suite = rsn.group_cipher_suite();
	group_cipher_suite_item->appendRow(oui_row(group_cipher_suite.oui));
	group_cipher_suite_item->appendRow(cipher_type_row(group_cipher_suite.type));
	appendRow(group_cipher_suite_item);

	appendRow({new QStandardItem("Pairwise Suite Count"),
	           new QStandardItem(QString::number(rsn.pairwise_cipher_suite_count()))});

	for (const auto &pairwise_cipher_suite : rsn.pairwise_cipher_suites()) {
		QStandardItem *pairwise_cipher_suite_item = new QStandardItem("Pairwise Cipher Suite");
		pairwise_cipher_suite_item->appendRow(oui_row(pairwise_cipher_suite.oui));
		pairwise_cipher_suite_item->appendRow(cipher_type_row(pairwise_cipher_suite.type));
		appendRow(pairwise_cipher_suite_item);
	}

	appendRow({new QStandardItem("Auth Key Management (AKM) Suite Count"),
	           new QStandardItem(QString::number(rsn.akm_suite_count()))});

	for (const auto &akm_suite : rsn.akm_suites()) {
		QStandardItem *akm_suite_item = new QStandardItem("AKM Suite");
		akm_suite_item->appendRow(oui_row(akm_suite.oui));
		akm_suite_item->appendRow(akm_suite_row(akm_suite.type));
		appendRow(akm_suite_item);
	}
}
