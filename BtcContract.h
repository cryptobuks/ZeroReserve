/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BTCCONTRACT_H
#define BTCCONTRACT_H

#include "zrtypes.h"
#include "Currency.h"
#include "zrdb.h"

#include <vector>


/**
 * @brief Bitcoin sale contract
 *
 * This class implements a local contract of money transfer with a friend. The
 * conditions of the contract will be monitored. The money
 * is released when an agreed upon Bitcoin transaction has at least 6 confirmations.
 *
 * Sender's main pupose is to poll the conditions for a payment
 * Receiver's main purpose is to poll the conditions for payment and check whether the
 * payment arrives. If not, user need to be notified
 */

class BtcContract
{
public:
    /** which side of the contract are we. Hops have 2 contracts that cancel each other out */
    enum Party { RECEIVER=0, SENDER };

    BtcContract(const ZR::ZR_Number & btcAmount, const ZR::ZR_Number & fee, const ZR::ZR_Number & price, const std::string & currencySym, Party party, const std::string & counterParty , const qint64 creationtime = 0 );
    virtual ~BtcContract();

    /** make sure we survive a crash or a shutdown once we're committed */
    void persist();
    /** last steps of this deal - remove from DB */
    void finalize();

    bool isReceiver() const { return m_party == RECEIVER; }
    bool isSender() const { return m_party == SENDER; }
    bool isContract( const std::string & contractId ) const { return contractId == m_btcTxId; }

    const ZR::ZR_Number & getBtcAmount() const { return m_btcAmount; }
    void setBtcAmount( const ZR::ZR_Number & btcAmount );

    const ZR::ZR_Number getFiatAmount() const { return m_btcAmount * m_price; }
    const ZR::ZR_Number getFee() const { return m_fee; }
    const std::string & getCurrencySym() const { return m_currencySym; }
    const std::string & getCounterParty() const { return m_counterParty; }
    const std::string & getBtcTxId() const { return m_btcTxId; }
    Party getParty(){ return m_party; }
    const ZR::ZR_Number & getPrice() { return m_price; }
    const qint64 & getCreationTime(){ return m_creationtime; }
    const ZR::BitcoinAddress & getDestAddress(){ return m_destAddress; }

    void activate( bool val = true ){ m_activated = val; }
    void setBtcAddress( const ZR::BitcoinAddress & addr ){ m_destAddress = addr; }
    const ZR::BitcoinAddress & getBtcAddress(){ return m_destAddress; }
    void setBtcTxId( const ZR::TransactionId & id ){ m_btcTxId = id; }

private:
    /** check if our TX is in the blockchain and has sufficient confirmations */
    bool poll();
    void execute();
    void deallocateFunds( const ZR::ZR_Number & amount );

private:
    std::string m_btcTxId;            // checked for final payment
    ZR::ZR_Number m_btcAmount;        // checked for final payment
    ZR::ZR_Number m_price;
    std::string m_currencySym;
    Party m_party;
    std::string m_counterParty;
    bool m_activated;
    ZR::BitcoinAddress m_destAddress; // checked for final payment
    qint64 m_creationtime;
    ZR::ZR_Number m_fee;

public:
    typedef std::list< BtcContract* >::iterator ContractIterator;
    /** container for all active btcContracts */
    static std::list< BtcContract* > contracts;
    static RsMutex m_contractMutex;

    static void pollContracts();
    static void rmContract( BtcContract * contract );

    static const unsigned int reqConfirmations;
};

#endif // BTCCONTRACT_H
