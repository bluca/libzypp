/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#ifndef ZMART_KEYRINGCALLBACKS_H
#define ZMART_KEYRINGCALLBACKS_H

#include <stdlib.h>
#include <iostream>

#include <zypp/base/Logger.h>
#include <zypp/ZYppCallbacks.h>
#include <zypp/Pathname.h>
#include <zypp/KeyRing.h>
#include <zypp/Digest.h>

#include "zmart-misc.h"

///////////////////////////////////////////////////////////////////
namespace zypp {
/////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    // KeyRingReceive
    ///////////////////////////////////////////////////////////////////
    struct KeyRingReceive : public zypp::callback::ReceiveReport<zypp::KeyRingReport>
    {
      virtual bool askUserToAcceptUnsignedFile( const std::string &file )
      {
        cout << "\x1B 2K\r" << file << " is unsigned, continue? [y/n]: ";
        return readBoolAnswer();
      }
      
      virtual bool askUserToImportKey( const PublicKey &key )
      {
        if ( geteuid() != 0 )
          return false;
        
        cout << "\x1B 2K\r" << "Import key " << key.id() << " in trusted keyring? [y/n]: ";
        return readBoolAnswer();
      } 
      
      virtual bool askUserToAcceptUnknownKey( const std::string &file, const std::string &id )
      {
        cout << "\x1B 2K\r" << file << " is signed with an unknown key id: " << id << ", continue? [y/n]: ";
        return readBoolAnswer();
      }
      virtual bool askUserToTrustKey( const PublicKey &key )
      {
        cout  << "\x1B 2K\r" << "Do you want to trust key id " << key.id() << " " << key.name() << " fingerprint:" << key.fingerprint() << " ? [y/n]: " ;
        return readBoolAnswer();
      }
      virtual bool askUserToAcceptVerificationFailed( const std::string &file,const PublicKey &key )
      {
        cout << file << "Signature verification for " << file << " with public key id " << key.id() << " " << key.name() << " fingerprint:" << key.fingerprint() << " failed, THIS IS RISKY!. continue? [y/n]: " << endl;
        return readBoolAnswer();
      }
    };


    struct DigestReceive : public zypp::callback::ReceiveReport<zypp::DigestReport>
    {
      virtual bool askUserToAcceptNoDigest( const zypp::Pathname &file )
      {
        return readBoolAnswer();
      }
      virtual bool askUserToAccepUnknownDigest( const Pathname &file, const std::string &name )
      {
        return readBoolAnswer();
      }
      virtual bool askUserToAcceptWrongDigest( const Pathname &file, const std::string &requested, const std::string &found )
      {
        return readBoolAnswer();
      }
    };

    ///////////////////////////////////////////////////////////////////
}; // namespace zypp
///////////////////////////////////////////////////////////////////

class KeyRingCallbacks {

  private:
    zypp::KeyRingReceive _keyRingReport;

  public:
    KeyRingCallbacks()
    {
      _keyRingReport.connect();
    }

    ~KeyRingCallbacks()
    {
      _keyRingReport.disconnect();
    }

};

class DigestCallbacks {

  private:
    zypp::DigestReceive _digestReport;

  public:
    DigestCallbacks()
    {
      _digestReport.connect();
    }

    ~DigestCallbacks()
    {
      _digestReport.disconnect();
    }

};


#endif // ZMD_BACKEND_KEYRINGCALLBACKS_H
