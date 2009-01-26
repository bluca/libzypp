/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/VendorAttr.h
 *
*/
#ifndef ZYPP_VENDORATTR_H
#define ZYPP_VENDORATTR_H

#include <iosfwd>
#include <string>
#include <vector>

#include "zypp/base/NonCopyable.h"
#include "zypp/PathInfo.h"
#include "zypp/Vendor.h"

///////////////////////////////////////////////////////////////////
namespace zypp {
//////////////////////////////////////////////////////////////////

/** Definition of vendor equivalence.
 *
 * Packages with equivalment vendor strings may replace themself without
 * creating a solver error.
 *
 * Per default vendor strings starting with \c "suse' or \c 'opensuse"
 * are treated equivalent. This may be changed by providing customized
 * vendor description files in /etc/zypp/vendors.d.
 *
 * \todo remove superfluous base::NonCopyable
*/
class VendorAttr : private base::NonCopyable
{
  public:
    typedef std::vector<std::string> VendorList;

    /** Singleton */
    static const VendorAttr & instance();

    /**
     * Adding new equivalent vendors described in a directory
     **/
    bool addVendorDirectory( const Pathname & dirname ) const;

    /**
     * Adding new equivalent vendors described in a file
     **/
    bool addVendorFile( const Pathname & filename ) const;

    /**
     * Adding new equivalent vendor set from list
     **/
    template <class _Iterator>
    void addVendorList( _Iterator begin, _Iterator end ) const
    { VendorList tmp( begin, end ); _addVendorList( tmp ); }

    /** Return whether two vendor strings shold be treated as the same vendor.
     * Usually the solver is allowed to automatically select a package of an
     * equivalent vendor when updating. Replacing a package with one of a
     * different vendor usually must be confirmed by the user.
    */
    bool equivalent( const Vendor & lVendor, const Vendor & rVendor ) const;

  private:
    VendorAttr();
    void _addVendorList( VendorList & ) const;
};

/** \relates VendorAttr Stream output */
std::ostream & operator<<( std::ostream & str, const VendorAttr & obj );

///////////////////////////////////////////////////////////////////
}; // namespace zypp
///////////////////////////////////////////////////////////////////

#endif // ZYPP_VENDORATTR_H
