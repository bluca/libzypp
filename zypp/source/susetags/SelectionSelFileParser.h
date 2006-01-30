/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/parser/tagfile/Parser.h
 *
*/
#ifndef ZYPP_PARSER_TAGFILE_SelectionSelFilePARSER_H
#define ZYPP_PARSER_TAGFILE_SelectionSelFilePARSER_H

#include <iosfwd>
#include <set>
#include <map>
#include <list>

#include "zypp/parser/tagfile/TagFileParser.h"
#include "zypp/parser/tagfile/ParseException.h"
#include "zypp/Selection.h"
#include "zypp/source/susetags/SuseTagsSelectionImpl.h"

#include "zypp/Pathname.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    namespace susetags
    { /////////////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////////////
      //
      //	CLASS NAME : SelectionSelFileParser
      //
      /** Tagfile parser. */
      struct SelectionSelFileParser : public zypp::parser::tagfile::TagFileParser
      {
        Selection::Ptr result;
        shared_ptr<SuseTagsSelectionImpl> selImpl;
        
        SelectionSelFileParser();
        virtual ~SelectionSelFileParser()
        {}

        void consume( const SingleTag &tag );
        void consume( const MultiTag &tag );
        void endParse();
      };
      ///////////////////////////////////////////////////////////////////
      Selection::Ptr parseSelection( const Pathname & file_r );
      /////////////////////////////////////////////////////////////////
    } // namespace source
    ///////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
  } // namespace susetags
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
//
#endif //  ZYPP_PARSER_TAGFILE_SelectionSelFilePPARSER_H
