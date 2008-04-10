/*
 *  LibAxl:  Another XML library
 *  Copyright (C) 2008 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1 of
 *  the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to
 *  develop proprietary applications using this library without any
 *  royalty or fee but returning back any change, improvement or
 *  addition in the form of source code, project image, documentation
 *  patches, etc. 
 *
 *  For commercial support on build XML enabled solutions contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         Edificio Alius A, Oficina 102,
 *         C/ Antonio Suarez Nº 10,
 *         Alcalá de Henares 28802 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/xml
 */

#include <axl_babel.h>

#define LOG_DOMAIN "axl-babel"

/** 
 * @brief Allows to configure babel encoding functions making axl
 * library to use its API to support encoding formats.
 * 
 * @param error An optional reference to an axlError where failure
 * will be notified.
 * 
 * @return true if the init operation was properly implemented,
 * otherwise false is returned.
 */
bool        axl_babel_init (axlError ** error)
{
	/* call to configure babel */
	axl_doc_set_detect_codification_func    (axl_babel_detect_codification, NULL);
	axl_doc_set_configure_codification_func (axl_babel_configure_encoding, NULL);

	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "configure axl-babel handlers..");

	return true;
}

/** 
 * @brief Remove handlers installed and babel configuration from base
 * library.
 */
void        axl_babel_finish ()
{
	/* call to configure babel */
	axl_doc_set_detect_codification_func    (NULL, NULL);
	axl_doc_set_configure_codification_func (NULL, NULL);

	return;
}

/** 
 * @internal Library function that allows to detect entity codification
 * found to use the appropiate built-in decoder handler until the
 * right codification is found (due to encoding header
 * declaration). The intention is to move the content read from the
 * stream abstraction into a utf-8 unified representation inside
 * memory.
 * 
 * @param doc The document that is about to be checked for the
 * appropiate codification.
 *
 * @param encoding Detected encoding by the function.
 *
 * @param error The reference where errors will be reported.
 * 
 * @return true if the codification detection was performed properly,
 * otherwise false is returned if an error is found.
 */
bool axl_babel_detect_codification (axlStream  * stream, 
				    char      ** encoding,
				    axlPointer   user_data,
				    axlError  ** error)
{
	/* check basic case where the stream have no content to
	 * parse */
	if (axl_stream_get_size (stream) < 4) {
		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "unable to detect codification, stream received doesn't have enough content to parse");
		return false;
	} /* end if */

	/* clear encoding */
	if (encoding)
		(*encoding) = NULL;

	/* Check built-in supported formats. First check for documents
	 * with the BOM mark configured */
	
	/* check UTF-8 BOM: EF BB BF */
	if (axl_stream_inspect_code (stream, (char) 239, 0) &&
	    axl_stream_inspect_code (stream, (char) 187, 1) &&
	    axl_stream_inspect_code (stream, (char) 192, 2)) {

		/* configure encoding detected */
		if (encoding)
			(*encoding) = "utf8";

		/* update stream */
		axl_stream_move (stream, axl_stream_get_index (stream) + 3);

		/* found utf-8 encoding, install associated filter */
		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "utf-8 BOM mark found, assuming utf-8 content");
		return true;
	} /* end if */

	/* check UTF-16 (little-endian) BOM: FF FE */
	if (axl_stream_inspect_code (stream, (char) 255, 0) &&
	    axl_stream_inspect_code (stream, (char) 254, 1)) {
		/* configure encoding detected */
		if (encoding)
			(*encoding) = "utf16";

		/* update stream */
		axl_stream_move (stream, axl_stream_get_index (stream) + 2);

		/* found utf-16 encoding, install associated filter */
		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "utf-16 BOM mark found, assuming utf-16 content");
		return true;
	}

	/* check UTF-32 (little-endian) BOM: FF FE 00 00 */
	if (axl_stream_inspect_code (stream, (char) 255, 0) &&
	    axl_stream_inspect_code (stream, (char) 254, 1) &&
	    axl_stream_inspect_code (stream, (char) 0, 2) &&
	    axl_stream_inspect_code (stream, (char) 0, 3)) {
		/* configure encoding detected */
		if (encoding)
			(*encoding) = "utf32";

		/* update stream */
		axl_stream_move (stream, axl_stream_get_index (stream) + 4);

		/* found utf-16 encoding, install associated filter */
		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "utf-32 BOM mark found, assuming utf-8 content");
		return true;
	} /* end if */

	/* NO BOM MARK SECTION */

	/* detect utf-8, iso 646, ascii,...*/
	if (axl_stream_inspect_code (stream, (char) 60, 0) &&
	    axl_stream_inspect_code (stream, (char) 63, 1) &&
	    axl_stream_inspect_code (stream, (char) 120, 2) &&
	    axl_stream_inspect_code (stream, (char) 109, 3)) {
		/* no encoding detected we are not sure */ 
		
		/* found utf-16 encoding, install associated filter */
		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "found utf-8, iso 646, ascii or something similiar without mark, assuming utf-8 until encoding declaration..");
		return true;
	} /* end if */

	/* unable to detect the encoding format */
	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, 
		   "unable to detect encoding format, failed to detect encoding format");
	axl_error_new (-1, "unable to detect encoding format, failed to detect encoding format", NULL, error);
	return false;
	
}

/** 
 * @internal Function that implements the identity operation. Does
 * nothing just translates data from source to output.
 */
int axl_babel_identity_utf8 (const char * source, int source_size,
			     const char * source_encoding,
			     char * output, int output_size, 
			     int  * output_converted,
			     int  * remain_source_index,
			     axlPointer user_data)
{
	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "received request to translate source code from iso-8859-15 to utf-8: source size=%d: %s",
		   source_size, source);

	/* identity operation */
	memcpy (output, source, source_size);
	(*output_converted) = source_size;
	
	/* operation completed */
	return 1;
}

/** 
 * @internal Function that performs translation between iso-8859-15
 * and utf-8.
 * 
 * @return The handler must return 1 if the operation was completed, 2
 * if the operation was completed but not enough size was found on
 * output buffer to store the content or 0 if the function fails.
 */
int axl_babel_iso885915_utf8 (const char * source, int source_size,
			      const char * source_encoding,
			      char * output, int output_size, 
			      int  * output_converted,
			      int  * remain_source_index,
			      axlPointer user_data)
{
	axlBabelTable * table = (axlBabelTable *)user_data;
	int             iterator;
	int             iterator2;
	int             desp;
	unsigned char   value;

	
	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "received request to translate source code from iso-8859-15 to utf-8: source size=%d on output size=%d: %s",
		   source_size, output_size, source);

	iterator  = 0;
	iterator2 = 0;
	while (iterator < source_size && iterator2 < output_size) {
		
		/* get the value */
		value = source[iterator];

		/* __axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "translating value=%c (%d)", source[iterator], value); */

		/* check if we are able to place all the encoded item */
		if ((iterator2 + table[value].size) > output_size) {
			/* __axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "unable to completely decode following sequence (%d size, on remain: %d)",
			   table[value].size, output_size - iterator2); */
			break;
		}
		
		desp = 0;
		while ((desp < table[value].size)) {
			/* __axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "   configuring at %d value: %d", 
				   iterator2 + desp,
				   table[value].buffer[desp]); */
			output[iterator2] = table[value].buffer[desp];
			desp++;
			iterator2++;
		}

		/* next */
		iterator++;

	} /* end while */

	/* update output converted */
	*output_converted = iterator2;
	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "output converted=%d: %s (iterator:%d == source_size:%d)", 
		   iterator2, output, iterator, source_size);

	/* check exit condition (if all output was converted) */
	if (iterator == source_size) 
		return 1;

	/* source to be converted remains */
	*remain_source_index = iterator;
	return 2;
}


/** 
 * @internal Function that tries to check encoding found to configure the
 * proper set of functions to translate from and to utf-8.
 *
 * @param stream Stream to be configured.
 * 
 * @param encoding Encoding declaration found at the xml header.
 *
 * @param detected Detected encoding found by the detect codification
 * configured.
 *
 * @param user_data User defined pointer.
 * 
 * @param error An optional error that will be filled in the case an
 * error is found.
 * 
 * @return true if the operation was completed, otherwise false is
 * returned.
 */
bool axl_babel_configure_encoding (axlStream  * stream, 
				   const char * encoding, 
				   const char * detected, 
				   axlPointer user_data, axlError ** error)
{
	axlBabelTable * table;

	__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "configuring final document enconding, previously detected=%s, declared=%s",
		   detected ? detected : "none",
		   encoding ? encoding : "none");

	/* check case were a encoding was detected (the entity content
	 * is encoded as detected due to marks or other means) */
	if (detected) {
		
	} else {
		/* No encoding detected or it was too open to clearly
		 * define the codification. Then use the encoding
		 * attribute found at the xml header. */
		if (axl_cmp (encoding, "iso885915")) {
			__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "installed handler encoding for iso-8859-15");

			/* install a translator handler */
			table = axl_babel_build_iso885915_table ();

			/* associate to the stream */
			axl_stream_link_full (stream, table, axl_free, true);

			if (! axl_stream_setup_decode (stream, encoding, axl_babel_iso885915_utf8, table, error))
				return false; 
		} /* end if */
	} /* end if (doc->detected_encoding) */
	
	return true;
}

/** 
 * @brief Allows to check if the provided string is in utf-8 coding
 * form.
 * 
 * @param content The content to length.
 *
 * @param content_length Length (in octets) of the string received. If
 * provided -1, content will be calculated using strlen function.
 *
 * @param index_error Optional reference where will be reported the
 * index position that caused the error.
 *
 * @return true if the content provided is all in utf-8 otherwise
 * false is returned. In the case index_error or error is defined and
 * an error is found, they are defined to the appropriate value.
 */
bool        axl_babel_check_utf8_content  (const char  * content,
					   int           content_length,
					   int         * index_error)
{
	int           iterator = 0;
	unsigned char value;


	if (index_error)
		*index_error = 0;

	axl_return_val_if_fail (content, false);
	axl_return_val_if_fail (content_length >= -1, false);

	/* check and calculate content */
	if (content_length == -1)
		content_length = strlen (content);

	while (iterator < content_length) {
		/* utf with 4 octects */
		value = content[iterator];
		if (value >= 240 && value <= 247 && (iterator + 1) < content_length ) {
			
			/* get next value */
			value = content[iterator + 1];
			if (value >= 128 && value <= 191 && (iterator + 2) < content_length ) {

				/* get next value */
				value = content[iterator + 2];
				if (value >= 128 && value <= 191 && (iterator + 3) < content_length ) {
					
					/* get next value */
					value = content[iterator + 3];
					if (value >= 128 && value <= 191) {
						iterator += 4;
						continue;
					} /* end if */
				}
			}

			__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "found error while detecting 4 octect utf-8 format..");
			/* found error */
			if (index_error)
				*index_error = iterator;
			return false;
		} /* end if */
			
		/* utf with 3 octects */
		if (value >= 224 && value <= 239  && (iterator + 1) < content_length ) {
			/* get next value */
			value = content[iterator + 1];
			if (value >= 128 && value <= 191 && (iterator + 2) < content_length ) {

				/* get next value */
				value = content[iterator + 2];
				if (value >= 128 && value <= 191) {
					iterator += 3;
					continue;
				} /* end if */
			}

			__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "found error while detecting 3 octect utf-8 format..");
				
			/* found error */
			if (index_error)
				*index_error = iterator;
			return false;
		} 

		/* utf with 2 octects */
		if (value >= 192 && value <= 223  && (iterator + 1) < content_length ) {
			/* get next value */
			value = content[iterator + 1];
			if (value >= 128 && value <= 191) {
				iterator += 2;
				continue;
			} /* end if */
			
			__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "found error while detecting 2 octect utf-8 format value=%d..", value);

			/* found error */
			if (index_error)
				*index_error = iterator;
			return false;
		} 

		if (value >= 0 && value <= 127 ) {
			iterator ++;
			continue;
		} /* end if */

		__axl_log (LOG_DOMAIN, AXL_LEVEL_DEBUG, "found error while detecting single octect utf-8 format..");

		/* found error */
		if (index_error)
			*index_error = iterator;
		return false;


	} /* end while */

	return true;
}