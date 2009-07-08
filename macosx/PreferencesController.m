
/**
 * OpenEmulator
 * Mac OS X Preferences Controller
 * (C) 2009 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls the preferences.
 */

#import "PreferencesController.h"

@implementation PreferencesController

- (id)init
{
	self = [super initWithWindowNibName:@"Preferences"];
	
	return self;
}

- (void)windowDidLoad
{
	[super windowDidLoad];
	
	NSToolbar *toolbar = [[NSToolbar alloc] initWithIdentifier:@"Preferences Toolbar"];
	NSString *selectedItemIdentifier = @"General";
	
	[toolbar setDelegate:self];
	[toolbar setAllowsUserCustomization:NO];
	[toolbar setDisplayMode:NSToolbarDisplayModeIconAndLabel];
	[toolbar setSizeMode:NSToolbarSizeModeRegular];
	[toolbar setSelectedItemIdentifier:selectedItemIdentifier];
	[[self window] setToolbar:toolbar];
	[toolbar release];
	
    [self setView:selectedItemIdentifier];
	
	[fUseTemplate setTitle:NSLocalizedString(@"Use template: Apple II", "Use template:")];
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar
	  itemForItemIdentifier:(NSString *)ident
  willBeInsertedIntoToolbar:(BOOL)flag
{
	NSToolbarItem *item = [[NSToolbarItem alloc] initWithItemIdentifier:ident];
	
	if ([ident isEqualToString:@"General"])
	{
		[item setLabel:NSLocalizedString(@"General", "Preferences -> toolbar item title")];
		[item setImage:[NSImage imageNamed:@"PRGeneral.png"]];
		[item setTarget:self];
		[item setAction:@selector(selectView:)];
		[item setAutovalidates:NO];
	}
	else if ([ident isEqualToString:@"Sound"])
	{
		[item setLabel:NSLocalizedString(@"Sound", "Preferences -> toolbar item title")];
		[item setImage:[NSImage imageNamed:@"PRSound.png"]];
		[item setTarget:self];
		[item setAction:@selector(selectView:)];
		[item setAutovalidates:NO];
	}
	else
	{
		[item release];
		return nil;
	}
	
	return [item autorelease];
}

- (NSArray *)toolbarSelectableItemIdentifiers:(NSToolbar *)toolbar
{
	return [self toolbarDefaultItemIdentifiers:toolbar];
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar *)toolbar
{
	return [self toolbarAllowedItemIdentifiers:toolbar];
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar *)toolbar
{
	return [NSArray arrayWithObjects:@"General", @"Sound", nil];
}

- (void)selectView:(id)sender
{
	[self setView:[sender itemIdentifier]];
}

- (void)setView:(NSString *)itemIdentifier
{
	NSView *view;
	if ([itemIdentifier isEqualToString:@"General"])
		view = fGeneralView;
	if ([itemIdentifier isEqualToString:@"Sound"])
		view = fSoundView;
	else
		view = fGeneralView;
	
    NSWindow *window = [self window];
    if ([window contentView] == view)
        return;
	
	[view setHidden:YES];
	
    NSRect windowRect = [window frame];
    float difference = ([view frame].size.height - [[window contentView] frame].size.height) *
		[window userSpaceScaleFactor];
    windowRect.origin.y -= difference;
    windowRect.size.height += difference;
	
    [window setContentView:view];
    [window setFrame:windowRect display:YES animate:YES];
    [view setHidden:NO];
    
	[window setTitle:NSLocalizedString(itemIdentifier, "Preferences view")];
}

- (void)chooseTemplate:(id)sender
{
	
}

@end
