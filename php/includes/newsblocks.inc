<?php
/**
 * Newsblocks Demo Includes
 *
 * These are the functions that do all of the heavy lifting for the demo.
 *
 * @package Newsblocks
 * @version 1.1.1
 * @author Ryan Parman
 * @link http://simplepie.org/wiki/tutorial/how_to_replicate_popurls Newsblocks tutorial page.
 * @license http://www.opensource.org/licenses/bsd-license.php BSD License
 */


/**
 * A wrapper for all of the functions used.
 */
class newsblocks
{

	/**
	 * Renders the display for a normal text-oriented feed.
	 *
	 * @access public
	 * @param mixed $url Either a single feed URL (as a string) or an array of feed URLs (as an array of strings).
	 * @param array $options Options that the function should take into account when rendering the markup. Accepts string 'title', string 'favicon', integer 'items', and string 'direction' => 'rtl'.
	 * @return string The (X)HTML markup to display on the page.
	 */
	function render($url, $options = null)
	{
		// Create a new SimplePie instance with this feed
		$feed = new SimplePie();
		$feed->set_feed_url($url);
		//set the cache time for generic newsblocks to 20 minutes
		$feed->set_cache_duration(1200);
		$feed->init();
		if ($feed->error())
		{
			echo $feed->error();
		}

		// Generate a unique identifier value for the URL(s) being used. HTML id attributes MUST begin with a letter.
		if (is_array($url))
		{
			$t = '';
			foreach ($url as $u)
			{
				$t .= $u;
			}
			$hash = 'a' . sha1($t);
		}
		else
		{
			$hash = 'a' . sha1($url);
		}

		// Open a <div> with a class of "block" (which we'll use for styling) and an id of some random value (for targetting via JavaScript)
		$html = '<div class="block" id="' . $hash . '">' . "\n";

		
		// Let's begin the primary list (the part we want to show when the page loads).
		if (isset($options['direction']) && $options['direction'] == 'rtl')
		{
			$direction = 'rtl';
		}
		else
		{
			$direction = 'ltr';
		}
		$html .= '<ul class="primary" style="direction:' . $direction . ';">' . "\n";

		// Loop through the first 10 items.
		if (isset($options['items']))
		{
			$items = intval($options['items']);
		}
		else
		{
			$items = 10;
		}
		foreach ($feed->get_items(0, $items) as $item)
		{
			$class = '';
			$type = '';
			$new = '';

			// Check to see if we have an enclosure so we can add a special icon
			if ($enclosure = $item->get_enclosure())
			{
				// Figure out the mime type of the enclosure
				$type = $enclosure->get_real_type();

				// Is it a video?
				if (stristr($type, 'video/') || stristr($type, 'x-shockwave-flash'))
				{
					$class = 'enclosure video';
				}

				// Is it audio?
				elseif (stristr($type, 'audio/'))
				{
					$class = 'enclosure audio';
				}

				// Is it an image?
				elseif (stristr($type, 'image/'))
				{
					$class = 'enclosure image';
				}
			}

			// Calculate 24 hours ago
			// $yesterday = time() - (24*60*60);

			// Compare the timestamp of the feed item with 24 hours ago.
			// if ($item->get_date('U') > $yesterday)
			// {
				// If the item was posted within the last 24 hours, let's add a "new" image to the end.
			//	$new = '<img src="./images/new.png" alt="New!" title="This was posted within the last 24 hours." />';
			// }

			// Determine the length to shorten the description to.
			if (isset($options['length']))
			{
				$length = $options['length'];
			}
			else
			{
				$length = 200;
			}

			// Add each item: item title, linked back to the original posting, with a tooltip containing the description.
			$html .= '<li class="' . $class . '"><a class="ctip" href="' . $item->get_permalink() . '" title="|' . newsblocks::cleanup($item->get_description(), $length) . '">' . $item->get_title() . '</a> </li>' . "\n";
		}

		// Close out of the primary list
		$html .= '</ul>' . "\n";

		// Let's begin the secondary list (the part that will show when we click on "More" below).
		$html .= '<ul class="secondary" style="direction:' . $direction . '; display:none;">' . "\n";

		// Loop through the remainder of the items, beginning where we left off last time.
		foreach ($feed->get_items($items) as $item)
		{
			$class = '';
			$type = '';
			$new = '';

			// Check to see if we have an enclosure so we can add a special icon
			if ($enclosure = $item->get_enclosure())
			{
				// Figure out the mime type of the enclosure
				$type = $enclosure->get_real_type();

				// Is it a video?
				if (stristr($type, 'video/') || stristr($type, 'x-shockwave-flash'))
				{
					$class = 'enclosure video';
				}

				// Is it audio?
				elseif (stristr($type, 'audio/'))
				{
					$class = 'enclosure audio';
				}

				// Is it an image?
				elseif (stristr($type, 'image/'))
				{
					$class = 'enclosure image';
				}
			}

			// Calculate 24 hours ago
			// $yesterday = time() - (24*60*60);

			// Compare the timestamp of the feed item with 24 hours ago.
			// if ($item->get_date('U') > $yesterday)
			// {
				// If the item was posted within the last 24 hours, let's add a "new" image to the end.
			//	$new = '<img src="./images/new.png" alt="New!" title="This was posted within the last 24 hours." />';
			// }

			// Determine the length to shorten the description to.
			if (isset($options['length']))
			{
				$length = $options['length'];
			}
			else
			{
				$length = 200;
			}

			// Add each item: item title, linked back to the original posting, with a tooltip containing the description.
			$html .= '<li class="' . $class . '"><a class="ctip" href="' . $item->get_permalink() . '" title="|' . newsblocks::cleanup($item->get_description(), $length) . '">' . $item->get_title() . '</a> </li>' . "\n";
		}

		// Close out of the secondary list
		$html .= '</ul>' . "\n";

		// If we have more than 10 items in the feed...
		if ($feed->get_item_quantity() > 10)
		{
			// Add a little "More" link for people to click on.
			$html .= '<p class="more"><a href="" class="more">More &raquo;</a></p>';
		}

		// Close out of this <div> block.
		$html .= '</div>' . "\n";

		// Return all of the HTML, so that we can display it as we choose or manipulate it further.
		return $html;
	}




	/**
	 * Renders the display for the flickr interesting feed.
	 *
	 * @access public
	 * @param mixed $url Either a single feed URL (as a string) or an array of feed URLs (as an array of strings).
	 * @param array $options Options that the function should take into account when rendering the markup. Accepts string 'title', string 'favicon', integer 'items', and string 'direction' => 'rtl'.
	 * @return string The (X)HTML markup to display on the page.
	 */
	function render_flickr($url, $options = null)
	{
		// Create a new SimplePie instance with this feed
		$feed = new SimplePie();
		$feed->set_feed_url($url);
		//set the cache time for generic newsblocks to 10 minutes
		$feed->set_cache_duration(600);
		//Make sure the feed is ordered by date
		$feed->enable_order_by_date(true);
		$feed->init();

		// Generate a unique identifier value for the URL(s) being used. HTML id attributes MUST begin with a letter.
		if (is_array($url))
		{
			$t = '';
			foreach ($url as $u)
			{
				$t .= $u;
			}
			$hash = 'a' . sha1($t);
		}
		else
		{
			$hash = 'a' . sha1($url);
		}

		// Open a <div> with a class of "wideblock" (which we'll use for styling) and an id of some random value (for targetting via JavaScript)
		$html = '<div class="wideblock" id="' . $hash . '">' . "\n";

	
		// Let's begin the primary list (the part we want to show when the page loads).
		if (isset($options['direction']) && $options['direction'] == 'rtl')
		{
			$direction = 'rtl';
		}
		else
		{
			$direction = 'ltr';
		}
		$html .= '<ul class="primary" style="direction:' . $direction . ';">' . "\n";

		// Loop through the first 10 items.
		if (isset($options['items']))
		{
			$items = intval($options['items']);
		}
		else
		{
			$items = 10;
		}
		foreach ($feed->get_items(0, $items) as $item)
		{
			$class = '';
			$type = '';
			$new = '';

			// Check to see if we have an enclosure so we can add a special icon
			if ($enclosure = $item->get_enclosure())
			{
				// Figure out the mime type of the enclosure
				$type = $enclosure->get_real_type();

				// Is it a video?
				if (stristr($type, 'video/') || stristr($type, 'x-shockwave-flash'))
				{
					$class = 'enclosure video';
				}

				// Is it audio?
				elseif (stristr($type, 'audio/'))
				{
					$class = 'enclosure audio';
				}

				// Is it an image?
				elseif (stristr($type, 'image/'))
				{
					$class = 'enclosure image';
				}
			}

			// Calculate 24 hours ago
			$yesterday = time() - (24*60*60);

			// Compare the timestamp of the feed item with 24 hours ago.
			if ($item->get_date('U') > $yesterday)
			{
				// If the item was posted within the last 24 hours, let's add a "new" image to the end.
				$new = '<img src="./images/new.png" alt="New!" title="This was posted within the last 24 hours." />';
			}

			// Determine the length to shorten the description to.
			if (isset($options['length']))
			{
				$length = $options['length'];
			}
			else
			{
				$length = 200;
			}

			//For youtube we need to isolate the thumbnail in the item contents
				//First, match all images in the content
				preg_match_all('/<img([^>]*)>/i', $item->get_content(), $matches);

				// Clear out the variable.
				$s = '';

				// Loop through all of the *complete* matches (stored in $matches[0]).
				foreach ($matches[0] as $match)
				{
					// Add the images (only) back to $s.
					$s .= $match;
				}
				
			
			// Add each item: item title, linked back to the original posting, with a tooltip containing the description.
//			$html .= '<li class="' . $class . '"><a href="' . $item->get_permalink() . '" title="' . newsblocks::cleanup($item->get_description(), $length) . '">' . $item->get_title() . '</a> ' . $new . '</li>' . "\n";
			//Create the html output for  youtube listings.  Basically we want the item permalink, the title and the image URI
			$html .= '<li class="flickr" ><a class="ctip" href="' . $item->get_permalink() . '" title="|' . newsblocks::cleanup($item->get_description(), $length) . '">' .$s . '</a></li>'."\n";
		}	

		// Close out of the primary list
		$html .= '</ul>' . "\n";

		// Close out of this <div> block.
		$html .= '</div>' . "\n";

		// Return all of the HTML, so that we can display it as we choose or manipulate it further.
		return $html;
	}

 	/**
	 * Renders a simpler, wider display for media-oriented feeds containing thumbnails.
	 *
	 * @access public
	 * @param mixed $url Either a single feed URL (as a string) or an array of feed URLs (as an array of strings).
	 * @param array $options Options that the function should take into account when rendering the markup. Currently only accepts integer 'items'. Intended for syntactic parity with newsblocks::render().
	 * @return string The (X)HTML markup to display on the page.
	 */
	function render_wide($url, $options = null)
	{
		// Create a new SimplePie instance with this feed
		$feed = new SimplePie();
		$feed->set_feed_url($url);
		$feed->init();

		// Generate a unique identifier value for the URL(s) being used. HTML id attributes MUST begin with a letter.
		if (is_array($url))
		{
			$t = '';
			foreach ($url as $u)
			{
				$t .= $u;
			}
			$hash = 'a' . sha1($t);
		}
		else
		{
			$hash = 'a' . sha1($url);
		}

		// Open a <div> with a class of "wideblock" (which we'll use for styling) and an id of some random value (for targetting via JavaScript)
		$html = '<div class="wideblock" id="' . $hash . '">' . "\n";
		
	

		// Let's begin the primary list (the part we want to show when the page loads).
		$html .= '<ul>' . "\n";

		// Loop through the first 10 items.
		if (isset($options['items']))
		{
			$items = intval($options['items']);
		}
		else
		{
			$items = 10;
		}
		foreach ($feed->get_items(0, $items) as $item)
		{
			// Check to see if we have an enclosure so we can add a special icon
			if ($enclosure = $item->get_enclosure())
			{
				// Check to see if we have a thumbnail.  We need it because this is going to display an image.
				if ($thumb = $enclosure->get_thumbnail())
				{
					// Add each item: item title, linked back to the original posting, with a tooltip containing the description.
					$html .= '<li><a class="ctip" href="' . $item->get_permalink() . '" title="|' . $item->get_title() . '"><img src="' . $thumb . '" alt="' . $item->get_title() . '" border="0" /></a></li>' . "\n";
				}
			}
		}

		// Close out of the primary list
		$html .= '</ul>' . "\n";

		// Close out of this <div> block.
		$html .= '</div>' . "\n";

		// Return all of the HTML, so that we can display it as we choose or manipulate it further.
		return $html;
	}


	/**
	 * Cleans up text for special output.
	 *
	 * Namely for use inside 'title' attributes. Strips HTML, removes double-quotes (since 
	 * that's what this demo uses for attributes), reduces all linebreaks and multiple 
	 * spaces into a single space, and can shorten a string to a number of characters.
	 *
	 * @access public
	 * @param string $s The string of text to clean up.
	 * @param integer $length The number of characters to return in the description.
	 * @return string The cleaned up string.
	 */
	function cleanup($s, $length = 0)
	{
		// Strip out HTML tags.
	    $s = strip_tags($s);

		// Get rid of double quotes so they don't interfere with the title tag.
	    $s = str_replace('"', '', $s);

		// Strip out superfluous whitespace and line breaks.
	    $s = preg_replace('/(\s+)/', ' ', $s);

		// Convert all HTML entities to their character counterparts.
		$s = html_entity_decode($s, ENT_QUOTES, 'UTF-8');

		// Shorten the string to the number of characters requested, and strip wrapping whitespace.
		if ($length > 0 && strlen($s) > $length)
		{
			$s = trim(substr($s, 0, $length)) . '&hellip;';
		}

		// Return the value.
	    return $s;
	}



}
?>